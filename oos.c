#include <stdio.h>
#include <glib.h>
#include <math.h>
#include "oos.h"
#include "lib_maths.h"
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


/* quite good settings - dissertation*/
// #define STRENGTH_EXCITE 4
// #define STRENGTH_INHIBIT -8

// new settings - trying to have excitation (at least, from apply set) exert a steadier influence
#define STRENGTH_EXCITE 0.35
#define STRENGTH_INHIBIT -8




/* RECENCY_CONSTANT - proportion of activation new item entering
   buffer steals from existing items */
#define RECENCY_CONSTANT 0.5  
#define RECENCY_UPPER_DECAY_THRESHOLD 0.3
#define DEFAULT_ELEMENT_ACTIVATION 0.85

char *oos_class_name[BOX_TYPE_MAX] = {
    "Process", "Buffer"
};

char *oos_message_type_name[MT_MAX] = {
    "Send", "Add", "Delete", "Excite", "Inhibit", "Clear", "Stop"
};

/******************************************************************************/
/* functions for gaussian random generator (for WM decay function) */

gsl_rng * gaussian_random_generator_create ()
{
  gsl_rng * r;
  const gsl_rng_type * R;
  R = gsl_rng_default;
  r = gsl_rng_alloc (R);
  gsl_rng_env_setup ();
  gsl_rng_set (r, time(0));
  return r;

}

void gaussian_random_generator_destroy (gsl_rng * r)
{
  gsl_rng_free (r);
}


/*****************************************************************************/


static void timestamped_clause_list_free(TimestampedClauseList *list)
{
    while (list != NULL) {
        TimestampedClauseList *tail = list->tail;
        pl_clause_free(list->head);
        free(list);
        list = tail;
    }
}

static int timestamped_clause_list_length(TimestampedClauseList *list)
{
    int n = 0;
    while (list != NULL) {
        list = list->tail;
        n++;
    }
    return(n);
}

static TimestampedClauseList *timestamped_clause_list_copy(TimestampedClauseList *clauses)
{
    TimestampedClauseList dummy, *tmp, *current = &dummy;

    for (tmp = clauses; tmp != NULL; tmp = tmp->tail) {
        if ((current->tail = (TimestampedClauseList *)malloc(sizeof(TimestampedClauseList))) == NULL) {
            return(NULL);      // failed malloc
        }
        else {
            current = current->tail;
            current->head = pl_clause_copy(tmp->head);
            current->activation = tmp->activation;
            current->timestamp = tmp->timestamp;
        }
    }
    current->tail = NULL;
    return(dummy.tail);
}

static TimestampedClauseList *timestamped_clause_list_reverse(TimestampedClauseList *list)
{
    TimestampedClauseList *prev = list;

    if (prev != NULL) {
        TimestampedClauseList *next = prev->tail;
        prev->tail = NULL;
        while (next != NULL) {
            TimestampedClauseList *tmp = next->tail;
            next->tail = prev;
            prev = next;
            next = tmp;
        }
    }
    return(prev);
}

static void timetamped_clause_list_swap_elements(TimestampedClauseList *list, int i, int r)
{
    if (i != r) {
        TimestampedClauseList *il = NULL;
        TimestampedClauseList *rl = NULL;
        TimestampedClauseList *this;

        for (this = list; this != NULL; this = this->tail) {
            if (i == 0) {
                il = this;
            }
            if (r == 0) {
                rl = this;
            }
            i--;
            r--;
        }

        if ((il == NULL) || (rl == NULL)) {
            fprintf(stdout, "WARNING: Failed to find element(s) in %s\n", __FUNCTION__);
        }
        else {
            TimestampedClauseList tmp;

            tmp.head = il->head;
            tmp.timestamp = il->timestamp;
            tmp.activation = il->activation;

            il->head = rl->head;
	    rl->head = tmp.head;

            il->timestamp = rl->timestamp;
	    rl->timestamp = tmp.timestamp;

            il->activation = rl->activation;
            rl->activation = tmp.activation;
        }
    }
}

static TimestampedClauseList *timestamped_clause_list_permute(TimestampedClauseList *list)
{
    int i, r, l;

    l = timestamped_clause_list_length(list);

    for (i = 0; i < l; i++) {
        r = random_integer(i, l);
        timetamped_clause_list_swap_elements(list, i, r);
    }
    return(list);
}

static TimestampedClauseList *timestamped_clause_list_delete_nth(TimestampedClauseList *list, int n)
{

    /* Delete the nth element, counting from zero */

    if (list == NULL) {
        return(NULL);
    }
    else if (n == 0) {
        TimestampedClauseList *result;

        result = list->tail;
        pl_clause_free(list->head);
        free(list);
        return(result);
    }
    else {
        TimestampedClauseList *prev = NULL, *this = list;
        while ((this != NULL) && (n-- > 0)) {
            prev = this;
            this = this->tail;
        }
        prev->tail = this->tail;
        pl_clause_free(this->head);
        free(this);
        return(list);
    }
}

static TimestampedClauseList *timestamped_clause_list_prepend_element(TimestampedClauseList *list, ClauseType *element, long now, double activation)
{
    TimestampedClauseList *new = (TimestampedClauseList *) malloc(sizeof(TimestampedClauseList));

    if (new == NULL) {
        return(list);
    }
    else {
        new->head = element;
        new->timestamp = now;
        new->activation = activation;
        new->tail = list;
        return(new);
    }
}

static TimestampedClauseList *timestamped_clause_list_add_element_to_tail(TimestampedClauseList *list, ClauseType *element, long now, double activation)
{
    TimestampedClauseList *node = (TimestampedClauseList *) malloc(sizeof(TimestampedClauseList));

    if (node == NULL) {
        fprintf(stdout, "WARNING: Memory allocation failed when appending element to timestamped list\n");
        return(list);
    }
    else if (element != NULL) {
        node->head = element;
        node->timestamp = now;
        node->activation = activation;
        node->tail = NULL;
        if (list == NULL) {
            list = node;
        }
        else {
            TimestampedClauseList *tmp = list;
            while (tmp->tail != NULL) {
                tmp = tmp->tail;
            }
            tmp->tail = node;
        }
    }
    return(list);
}

/******************************************************************************/

void random_initialise()
{
    srand(time(NULL));
}

int random_integer(int min, int max)
{
    // Return a random integer >= min, < max
    return((int) (min + rand() * ((max - min) / ((double) RAND_MAX+1))));
}

double random_uniform(double min, double max)
{
    // Return a random double >= min, <= max
    return(min + rand() * ((max - min) / (double) RAND_MAX));
}

static BoxList *oos_locate_box_ptr(OosVars *gv, int id)
{
    BoxList *tmp;

    for (tmp = gv->components; tmp != NULL; tmp = tmp->next) {
        if (tmp->id == id) {
            return(tmp);
        }
    }
    return(NULL);
}

char *oos_box_name(OosVars *gv, int id)
{
    BoxList *this = oos_locate_box_ptr(gv, id);

    if (this == NULL) {
        return(gv->name);
    }
    else {
        return(this->name);
    }
}

/******************************************************************************/
/* Initialisation functions: **************************************************/

void oos_messages_free(OosVars *gv)
{
    while (gv->messages != NULL) {
        MessageList *tmp = gv->messages->next;
        pl_clause_free(gv->messages->content);
        g_free(gv->messages);
        gv->messages = tmp;
    }
}

void oos_annotations_free(OosVars *gv)
{
    while (gv->annotations != NULL) {
        AnnotationList *tmp = gv->annotations->next;
        g_free(gv->annotations->text);
        g_free(gv->annotations);
        gv->annotations = tmp;
    }
}

void oos_arrows_free(OosVars *gv)
{
    while (gv->arrows != NULL) {
        ArrowList *tmp = gv->arrows->next;
        g_free(gv->arrows->coordinates);
        g_free(gv->arrows);
        gv->arrows = tmp;
    }
}

void oos_components_free(OosVars *gv)
{
    while (gv->components != NULL) {
        BoxList *tmp = gv->components->next;
        timestamped_clause_list_free(gv->components->content);
        g_free(gv->components->name);
        g_free(gv->components);
        gv->components = tmp;
    }
}

/*----------------------------------------------------------------------------*/

AnnotationList *oos_annotation_create(OosVars *gv, char *text, double x, double y, int fontsize, double theta, Boolean italic)
{
    // Return pointer to new annotation, or NULL if it isn't created

    AnnotationList *new;

    if ((new = (AnnotationList *)(malloc(sizeof(AnnotationList)))) != NULL) {
        new->next = gv->annotations;
        new->text = string_copy(text);
        new->x = x;
        new->y = y;
        new->fontsize = fontsize;
        new->theta = theta;
        new->italic = italic;
        gv->annotations = new;
    }
    return(new);
}


ArrowList *oos_arrow_create(OosVars *gv, Boolean straight, ArrowHeadType head, CairoxPoint *coordinates, int points, double width)
{
    // Return pointer to new arrow, or NULL if it isn't created

    ArrowList *new;

    if ((new = (ArrowList *)(malloc(sizeof(ArrowList)))) != NULL) {
        new->next = gv->arrows;
        new->straight = straight;
        new->head = head;
        new->coordinates = coordinates;
        new->points = points;
        new->width = width;
        gv->arrows = new;
    }
    return(new);
}


BoxList *oos_process_create(OosVars *gv, char *name, int id, double x, double y, void (*output_function)(OosVars *))
{
    // Return pointer to new box, or NULL if it isn't created

    BoxList *new;

    if ((new = (BoxList *)(malloc(sizeof(BoxList)))) != NULL) {
        new->next = gv->components;
        new->name = string_copy(name);;
        new->id = id;
        new->x = x;
        new->y = y;
        new->bt = BOX_PROCESS;
        new->stopped = FALSE;
        new->output_function = output_function;
        new->content = NULL;
        gv->components = new;
    }
    return(new);
}

/*  BROKEN CODE
BoxList *oos_buffer_create(OosVars *gv, char *name, int id, double x, double y, BufferDecayProp decay, int decay_constant, BufferCapacityProp capacity, int capacity_constant, BufferExcessProp excess_capacity, BufferAccessProp access, SpreadingActivationToggle spreading_activation, double (*spreading_activation_weights)[10]) 

*/

/* working code */
 BoxList *oos_buffer_create(OosVars *gv, char *name, int id, double x, double y, BufferDecayProp decay, int decay_constant, BufferCapacityProp capacity, int capacity_constant, BufferExcessProp excess_capacity, BufferAccessProp access)


{
    // Return pointer to new box, or NULL if it isn't created

    BoxList *new;

    if ((new = (BoxList *)(malloc(sizeof(BoxList)))) != NULL) {
        new->next = gv->components;
        new->name = string_copy(name);
        new->id = id;
        new->x = x;
        new->y = y;
        new->bt = BOX_BUFFER;
        new->stopped = FALSE;
        new->output_function = NULL;
        new->decay = decay;
        new->decay_constant = decay_constant;
        new->capacity = capacity;
        new->capacity_constant = capacity_constant;
        new->excess_capacity = excess_capacity;
        new->access = access;
	// new->spreading_activation = spreading_activation; // NS - comment this line
      	// new->spreading_activation_weights = spreading_activation_weights; // NS comment this line
        new->content = NULL;
        gv->components = new;
    }
    return(new);
}

void oos_buffer_create_element(OosVars *gv, int box_id, char *element, double activation)
{
    BoxList *this = oos_locate_box_ptr(gv, box_id);

    if (this == NULL) {
        fprintf(stdout, "WARNING: Cannot locate buffer %d in oos_buffer_create_element\n", box_id);
    }
    else {
        this->content = timestamped_clause_list_prepend_element(this->content,  pl_clause_make_from_string(element), gv->cycle, activation);
    }
}

/*----------------------------------------------------------------------------*/

OosVars *oos_globals_create()
{
    OosVars *gv;

    if ((gv = (OosVars *)malloc(sizeof(OosVars))) != NULL) {
        gv->cycle = 0;
        gv->block = 0;
        gv->name = NULL;
        gv->stopped = FALSE;
        gv->task_data = NULL;
        gv->components = NULL;
        gv->annotations = NULL;
        gv->arrows = NULL;
        gv->messages = NULL;
        oos_initialise_session(gv);
    }
    random_initialise();
    return(gv);
}

void oos_globals_destroy(OosVars *gv)
{
    if (gv != NULL) {
        g_free(gv->name);
        oos_components_free(gv);
        oos_annotations_free(gv);
        oos_arrows_free(gv);
        oos_messages_free(gv);
	gaussian_random_generator_destroy(gv->random_generator);
        free(gv);
    }
}

/*----------------------------------------------------------------------------*/

ClauseType *unify_terms(ClauseType *template, ClauseType *term)
{
    ClauseType *result = NULL;

    /* This implementation of unification is incomplete - it doesn't deal */
    /* correctly with variables that occur more than once in either term. */

    if ((pl_clause_type(term) == VAR) && (pl_clause_type(template) != NULL_TERM)) {
        /* We're matching against a variable: return TRUE unless the thing  */
        /* where matching is a NULL_TERM (which shouldn't happen)           */
        result = pl_clause_copy(template);
    }
    else {
        switch (pl_clause_type(template)) {
            case NULL_TERM: {
                break;
            }
            case EMPTY_LIST: {
                if (pl_clause_type(term) == EMPTY_LIST) {
                    result = pl_clause_copy(term);
                }
                break;
            }
            case INT_NUMBER: {
                if ((pl_clause_type(term) == INT_NUMBER) && (pl_integer(template) == pl_integer(term))) {
                    result = pl_clause_copy(term);
                }
                break;
            }
            case REAL_NUMBER: {
                if ((pl_clause_type(term) == REAL_NUMBER) && (pl_double(template) == pl_double(term))) {
                    result = pl_clause_copy(term);
                }
                break;
            }
            case STRING: {
                if ((pl_clause_type(term) == STRING) && (strcmp(pl_functor(template), pl_functor(term)) == 0)) {
                    result = pl_clause_copy(term);
                }
                break;
            }            
            case VAR: {
                result = pl_clause_copy(term);
                break;
            }
            case COMPLEX: {
                if (pl_arity(template) != pl_arity(term)) {
                    result = NULL;
                }
                else if (strcmp(pl_functor(template), pl_functor(term)) != 0) {
                    result = NULL;
                }
                else {
                    int i = pl_arity(term);
                    ClauseType *tmp;

                    result = pl_clause_copy(term);

                    /* Attempt to unify every argument... */
                    while ((i > 0) && ((tmp = unify_terms(pl_arg_get(template, i), pl_arg_get(term, i))) != NULL)) {
                        pl_arg_set(result, i, tmp);
                        i--;
                    }

                    /* And if we fail discard "result": */
                    if (i != 0) {
                        pl_clause_free(result);
                        result = NULL;
                    }
                }
                break;
            }
        }
    }
    return(result);
}

static Boolean terms_unify(ClauseType *term1, ClauseType *term2)
{
    // Check that terms unify, but don't actually unify them!

    ClauseType *result;

    if ((result = unify_terms(term1, term2)) == NULL) {
        return(FALSE);
    }
    else {
        pl_clause_free(result);
        return(TRUE);
    }
}

void oos_dump(OosVars *gv, Boolean state)
{
    // Debugging predicate: dump the model (and its state?)

    BoxList *tmp;

    fprintf(stdout, "%s: BLOCK %d; CYCLE %d\n", gv->name, gv->block, gv->cycle);
    if ((state) && (gv->messages)) {
        MessageList *ml;
        for (ml = gv->messages; ml != NULL; ml = ml->next) {
            fprintf(stdout, "  MESSAGE (");
            if ((tmp = oos_locate_box_ptr(gv, ml->source)) != NULL) {
                fprintf(stdout, "%s --> ", tmp->name ? tmp->name : "Unnamed");
            }
            else {
                fprintf(stdout, "Unknown --> ");
            }
            if ((tmp = oos_locate_box_ptr(gv, ml->target)) != NULL) {
                fprintf(stdout, "%s; %s): ", tmp->name ? tmp->name : "Unnamed", oos_message_type_name[ml->mt]);
            }
            else {
                fprintf(stdout, "%s; %s): ", "Unknown", oos_message_type_name[ml->mt]);
            }
            if (ml->content != NULL) {
                fprint_clause(stdout, ml->content);
            }
            if (ml->next != NULL) {
                fprintf(stdout, ", ");
            }
            fprintf(stdout, "\n");
        }
    }
    for (tmp = gv->components; tmp != NULL; tmp = tmp->next) {
        fprintf(stdout, "  COMPONENT: ");
        fprintf(stdout, "%s ", tmp->name ? tmp->name : "Unnamed");
        fprintf(stdout, "(%s)", oos_class_name[(int) tmp->bt]);
        if ((state) && (tmp->content != NULL)) {
            TimestampedClauseList *cl;
            fprintf(stdout, ": [");
            for (cl = tmp->content; cl != NULL; cl = cl->tail) {
                fprint_clause(stdout, cl->head);
                fprintf(stdout, "(%ld, %4.2f)", cl->timestamp, cl->activation);
                if (cl->tail != NULL) {
                    fprintf(stdout, ", ");
                }
            }
            fprintf(stdout, "]");
	}
        fprintf(stdout, "\n");
    }
}

/******************************************************************************/
/* Processing functions: ******************************************************/

Boolean oos_match_above_threshold(OosVars *gv, int id, ClauseType *template, double threshold)
{
    TimestampedClauseList *cl, *buffer_contents = NULL;
    ClauseType *result;
    BoxList *this = NULL;
    Boolean match = FALSE;

    /* Locate the buffer (for its content and access property): */
    this = oos_locate_box_ptr(gv, id);

    /* Get the buffer's content, suitably reordered: */
    if (this != NULL) {
        if (this->access == BUFFER_ACCESS_LIFO) {
            buffer_contents = timestamped_clause_list_copy(this->content);
        }
        else if (this->access == BUFFER_ACCESS_FIFO) {
            buffer_contents = timestamped_clause_list_reverse(timestamped_clause_list_copy(this->content));
        }
        else { // BUFFER_ACCESS_RANDOM
            buffer_contents = timestamped_clause_list_permute(timestamped_clause_list_copy(this->content));
        }
    }

    /* Attempt the match, unifying if it succeeds: */
    cl = buffer_contents;
    while ((cl != NULL) && (!match)) {
        if ((cl->activation >= threshold) && ((result = unify_terms(template, cl->head)) != NULL)) {
            pl_clause_swap(template, result);
            pl_clause_free(result);
            match = TRUE;
        }
        cl = cl->tail;
    }

    /* Free temporary copy and return the result: */
    timestamped_clause_list_free(buffer_contents);
    return(match);
}

/* NS - for propose response output - matches biggest buffer item that is above threshold */
Boolean oos_match_biggest_above_threshold(OosVars *gv, int id, ClauseType *template, double threshold)
{
    TimestampedClauseList *cl, *buffer_contents = NULL;
    ClauseType *result;
    BoxList *this = NULL;
    Boolean match = FALSE;
    double biggest_activation = 0;

    /* Locate the buffer (for its content and access property): */
    this = oos_locate_box_ptr(gv, id);

    /* Get the buffer's content, suitably reordered: */
    if (this != NULL) {
        if (this->access == BUFFER_ACCESS_LIFO) {
            buffer_contents = timestamped_clause_list_copy(this->content);
        }
        else if (this->access == BUFFER_ACCESS_FIFO) {
            buffer_contents = timestamped_clause_list_reverse(timestamped_clause_list_copy(this->content));
        }
        else { // BUFFER_ACCESS_RANDOM
            buffer_contents = timestamped_clause_list_permute(timestamped_clause_list_copy(this->content));
        }
    }

    /* Attempt the match, unifying if it succeeds: */
    cl = buffer_contents;
    while ((cl != NULL) && (!match)) {
      if ((cl->activation >= threshold) && 
	  (cl->activation >= biggest_activation) &&
	  ((result = unify_terms(template, cl->head)) != NULL)) {
	biggest_activation = cl->activation;
	pl_clause_swap(template, result);
	pl_clause_free(result);
	match = TRUE;
      }
        cl = cl->tail;
    }

    /* Free temporary copy and return the result: */
    timestamped_clause_list_free(buffer_contents);
    return(match);
}




Boolean oos_match(OosVars *gv, int id, ClauseType *template)
{
    return(oos_match_above_threshold(gv, id, template, 0.0));
}

void oos_message_create(OosVars *gv, MessageType mt, int source, int target, ClauseType *content)
{
    MessageList *new;

    if ((new = (MessageList *)malloc(sizeof(MessageList))) != NULL) {
        new->source = source;
        new->target = target;
        new->mt = mt;
        new->content = content;
        new->next = gv->messages;
        gv->messages = new;
    }
}

static void generate_messages(OosVars *gv)
{
    BoxList *tmp;

    for (tmp = gv->components; tmp != NULL; tmp = tmp->next) {
        if (!tmp->stopped && (tmp->bt == BOX_PROCESS) && (tmp->output_function != NULL)) {
            tmp->output_function(gv);
        }
    }
}

/*----------------------------------------------------------------------------*/


   

static void oos_buffer_apply_clear_messages(OosVars *gv, BoxList *this)
{
    MessageList *tmp;

    for (tmp = gv->messages; tmp != NULL; tmp = tmp->next) {
        if ((tmp->target == this->id) && (tmp->mt == MT_CLEAR)) {
            timestamped_clause_list_free(this->content);
            this->content = NULL;
        }
    }
}

static void oos_buffer_apply_delete_messages(OosVars *gv, BoxList *this)
{
    TimestampedClauseList *cl;
    MessageList *tmp;
    ClauseType *match;

    for (tmp = gv->messages; tmp != NULL; tmp = tmp->next) {
        if ((tmp->target == this->id) && (tmp->mt == MT_DELETE)) {
            if (this->content != NULL) {
                if ((match = unify_terms(this->content->head, tmp->content)) != NULL) {
                    TimestampedClauseList *tmp = this->content->tail;
                    pl_clause_free(this->content->head);
                    free(this->content);
                    this->content = tmp;
                    free(match);
                }
                else {
                    for (cl = this->content; cl->tail != NULL; cl = cl->tail) {
                        if ((match = unify_terms(cl->tail->head, tmp->content)) != NULL) {
                            TimestampedClauseList *rest = cl->tail->tail;
                            pl_clause_free(cl->tail->head);
                            free(cl->tail);
                            cl->tail = rest;
                            free(match);
                            break;
                        }
                    }
                }
            }
        }
    }
}

static void oos_buffer_apply_add_messages(OosVars *gv, BoxList *this)
{
    MessageList *tmp;

    for (tmp = gv->messages; tmp != NULL; tmp = tmp->next) { 
       if ((tmp->target == this->id) && (tmp->mt == MT_ADD)) {
            if ((this->capacity == BUFFER_CAPACITY_LIMITED) && !(timestamped_clause_list_length(this->content) < this->capacity_constant)) {
                if (this->excess_capacity == BUFFER_EXCESS_RANDOM) {
                    int r = random_integer(0, timestamped_clause_list_length(this->content));
                    this->content = timestamped_clause_list_delete_nth(this->content, r);
                    // Now prepend the new element:
                    this->content = timestamped_clause_list_prepend_element(this->content, pl_clause_copy(tmp->content), gv->cycle, DEFAULT_ELEMENT_ACTIVATION);
                }
                else if (this->excess_capacity == BUFFER_EXCESS_OLDEST) {
                    // Delete oldest (last) element
                    if ((this->content != NULL) && (this->content->tail == NULL)) {
                        // There's just one element - delete it:
                        pl_clause_free(this->content->head);
                        free(this->content);
                        this->content = NULL;
                    }
                    else if (this->content != NULL) {
                        // There are several elements - go to the second last:
                        TimestampedClauseList *tmp = this->content;
                        while (tmp->tail->tail != NULL) {
                            tmp = tmp->tail;
                        }
                        pl_clause_free(tmp->tail->head);
                        free(tmp->tail);
                        tmp->tail = NULL;
                    }
                    // Now prepend the new element:
                    this->content = timestamped_clause_list_prepend_element(this->content, pl_clause_copy(tmp->content), gv->cycle, DEFAULT_ELEMENT_ACTIVATION);
                }
                else if (this->excess_capacity == BUFFER_EXCESS_YOUNGEST) {
                    // Delete the youngest (first) element:
                    if (this->content != NULL) {
                        TimestampedClauseList *tmp = this->content;
                        this->content = this->content->tail;
                        pl_clause_free(tmp->head);
                        free(tmp);
                    }
                    // Now prepend the new element: 
                    this->content = timestamped_clause_list_prepend_element(this->content, pl_clause_copy(tmp->content), gv->cycle, DEFAULT_ELEMENT_ACTIVATION);
                }
            }
            else {
// fprintf(stdout, "%4d: Adding ", gv->cycle); fprint_clause(stdout, tmp->content); fprintf(stdout, " to %s\n", this->name);


	      /* RECENCY; adding element steals activation from elements in buffer */
	      if (this->decay == BUFFER_DECAY_RECENCY) {
		double stolen_activation = 0;
		double total_activation = 0;
		TimestampedClauseList *element = NULL;
		for (element = this->content; element != NULL; element = element->tail) {
		  total_activation += element->activation;
		  stolen_activation += (RECENCY_CONSTANT * element->activation);
		  element->activation *= (1-RECENCY_CONSTANT);
		}
		/* handle case where there is nothing in buffer 
	        if (stolen_activation == 0) {
		  stolen_activation = 1;
		} // */

		/* tops up total activation to stop activation leak */
		stolen_activation += (1-total_activation);
	     
                this->content = timestamped_clause_list_prepend_element(this->content, pl_clause_copy(tmp->content), gv->cycle, stolen_activation); 		
	      }
	      else {
                // No need to worry about capacity - just prepend the new element:
                this->content = timestamped_clause_list_prepend_element(this->content, pl_clause_copy(tmp->content), gv->cycle, DEFAULT_ELEMENT_ACTIVATION); 
	      }
            }
        }
    }
}

static Boolean message_excites_target(MessageList *message, long target_id, ClauseType *target_content)
{
    if (message->mt != MT_EXCITE) {
        return(FALSE);
    }
    else if (message->target != target_id) {
        return(FALSE);
    }
    else {
        return(terms_unify(message->content, target_content));
    }
}

static Boolean message_inhibits_target(MessageList *message, long target_id, ClauseType *target_content)
{
    if (message->mt != MT_INHIBIT) {
        return(FALSE);
    }
    else if (message->target != target_id) {
        return(FALSE);
    }
    else {
        return(terms_unify(message->content, target_content));
    }
}

static void oos_buffer_apply_activate_messages(OosVars *gv, BoxList *this)
{
    if ((this != NULL) && (this->bt = BOX_BUFFER)) {
        TimestampedClauseList *element;

        for (element = this->content; element != NULL; element = element->tail) {
            MessageList *tmp;
            int count = 0;

            for (tmp = gv->messages; tmp != NULL; tmp = tmp->next) {
                if (message_inhibits_target(tmp, this->id, element->head)) {
                    count--;
                }
                else if (message_excites_target(tmp, this->id, element->head)) {
                    count++;
                }
            }

            if (count > 0) {
	      //  element->activation *= 2.1;     //= 1.0; 
	      element->activation = apply_equations(element->activation, 1.0, STRENGTH_EXCITE, MT_SIGMOID);
              element->timestamp = gv->cycle;
            }
            else if (count < 0) {
	      // element->activation *= 0.1; // = 0.1;
	      element->activation = apply_equations(element->activation, 1.0, STRENGTH_INHIBIT, MT_SIGMOID);
                element->timestamp = gv->cycle;
            }
        }
    }
}


/* OLD, BROKEN CODE
static void oos_buffer_process_spreading_activation(OosVars *gv, BoxList *this, double spreading_activation_weights[10][10])
{
  if ((this != NULL) && (this->bt == BOX_BUFFER) && (this->spreading_activation == SPREADING_ACTIVATION_ON)) {
    TimestampedClauseList *element_i;

    // calculate vector of net excitation

    double net_excitation[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int i = 0;
    for (element_i = this->content; i < 10; element_i = element_i->tail) {
      // assumption that spreading_activation_weights[0] is the node representing 0... ??
      int j = 0;
      TimestampedClauseList *element_j;
      for (element_j = this->content; j < 10; element_j = element_j->tail) {
	net_excitation[i] += (element_j->activation * spreading_activation_weights[i][j]);
	j++;
      }

      i ++;
    }
    

    // apply new activations to current activations
    i = 0;
    for (element_i = this->content; i < 10; element_i = element_i->tail) {
      element_i->activation = apply_equations(element_i->activation, 0.95, net_excitation[i], MT_SIGMOID);
      i++;
    }


  }
}
 */

static Boolean element_survives_decay(OosVars *gv, ClauseType *element, long timestamp, double activation, BufferDecayProp decay, int decay_constant)
{
    switch (decay) {
        case BUFFER_DECAY_EXPONENTIAL: {
            double threshold = 1.0 / exp(log(2.0)/(double)decay_constant);
            double p = random_uniform(0.0, 1.0);
            return(p < threshold);
            break;
        }
        case BUFFER_DECAY_WEIBULL: {
            double dt = (gv->cycle - timestamp);
            if (dt > 0) {
                double threshold = 1.0 / pow(exp(1.0/(double)decay_constant), log(dt+1));
                double p = random_uniform(0.0, 1.0);
                return(p < threshold);
            }
            else {
                return(TRUE);
            }
            break;
        }
      

        case BUFFER_DECAY_RECENCY: {
	  
	  double threshold = (1/(1+(double)decay_constant));
	  double random_gaussian = gsl_ran_gaussian(gv->random_generator, threshold);
	  if (activation < (threshold + random_gaussian)) {
	    // printf ("FALSE: gaussian: %f, sd = %f\n", random_gaussian, threshold);
	    return (FALSE);

	  }
	  // printf ("TRUE: gaussian: %f, sd = %f\n", random_gaussian, threshold);
	  return (TRUE);
	  break;
	}
         

	  /* code works but is not very sophisticated
       case BUFFER_DECAY_RECENCY: {
	 
	 if (activation < random_uniform(0.0, (10/(double) (1 + decay_constant) ))) {
	    return (FALSE);
	 }

	  return (TRUE);
	  break;
	}
	  */
	  

        case BUFFER_DECAY_LINEAR: {
            double dt = (gv->cycle - timestamp);
            if (dt < decay_constant) {
                double threshold = 1.0 / (double) (decay_constant - dt);
                double p = random_uniform(0.0, 1.0);
                return(p > threshold);
            }
            else {
                return(FALSE);
            }
            break;
        }
        case BUFFER_DECAY_QUADRATIC: {
            double dt = (gv->cycle - timestamp);
            if (dt < decay_constant) {
                double k = 2.0;
                double threshold = pow(1.0 / (double) (decay_constant - dt), k);
                double p = random_uniform(0.0, 1.0);
                return(p > threshold);
            }
            else {
                return(FALSE);
            }
            break;
        }
        case BUFFER_DECAY_FIXED: {
            double dt = (gv->cycle - timestamp);
            return(dt < (decay_constant - 1));
            break;
        }
        case BUFFER_DECAY_NONE: {
            return(TRUE);
            break;
        }
    }
    fprintf(stdout, "WARNING: Buffer decay function not handled in switch statement\n");
    return(FALSE);
}

static void oos_buffer_apply_decay(OosVars *gv, BoxList *this, BufferDecayProp decay, int decay_constant)
{
    if ((this->content != NULL) && (decay != BUFFER_DECAY_NONE)) {
        TimestampedClauseList *before, *after, *tmp;

        before = this->content;
        after = NULL;
        
        while (before != NULL) {
	    if (element_survives_decay(gv, before->head, before->timestamp, before->activation, decay, decay_constant)) {
                after = timestamped_clause_list_add_element_to_tail(after, before->head, before->timestamp, before->activation);
            }
            else {
                pl_clause_free(before->head);
            }
            tmp = before->tail;
            free(before);
            before = tmp;
        }
        this->content = after;
    }
}

static void oos_component_process_stop_messages(OosVars *gv, BoxList *this)
{
    MessageList *tmp;

    for (tmp = gv->messages; tmp != NULL; tmp = tmp->next) {
        if ((tmp->target == this->id) && (tmp->mt == MT_STOP)) {
            this->stopped = TRUE;
        }
    }
}

static void update_component_state(OosVars *gv, BoxList *this)
{
    oos_component_process_stop_messages(gv, this);
    if (!this->stopped && (this->bt == BOX_BUFFER)) {
        // Process all the messages bound for the buffer:
        oos_buffer_apply_clear_messages(gv, this);
        oos_buffer_apply_delete_messages(gv, this);
        oos_buffer_apply_add_messages(gv, this);
        oos_buffer_apply_activate_messages(gv, this);
	// NS apply spreading activation
	// oos_buffer_process_spreading_activation (gv, this, this->spreading_activation_weights);

       // Now apply decay: 
        oos_buffer_apply_decay(gv, this, this->decay, this->decay_constant);
    }
}

static void update_states(OosVars *gv)
{
    BoxList *tmp;

    for (tmp = gv->components; tmp != NULL; tmp = tmp->next) {
        update_component_state(gv, tmp);
    }
}

static void oos_model_process_stop_messages(OosVars *gv)
{
    MessageList *tmp;

    for (tmp = gv->messages; tmp != NULL; tmp = tmp->next) {
        if ((tmp->target == 0) && (tmp->mt == MT_STOP)) {
            gv->stopped = TRUE;
        }
    }
}

static void oos_component_initialise_state(OosVars *gv, BoxList *this)
{
    if (this->content != NULL) {
        timestamped_clause_list_free(this->content);
        this->content = NULL;
    }
}

static void oos_component_initialise_states(OosVars *gv)
{
    BoxList *tmp;

    for (tmp = gv->components; tmp != NULL; tmp = tmp->next) {
        oos_component_initialise_state(gv, tmp);
    }
}

TimestampedClauseList  *oos_buffer_get_contents(OosVars *gv, int id)
{
    BoxList *this = oos_locate_box_ptr(gv, id);

    return(this ? this->content : NULL);
}

/*----------------------------------------------------------------------------*/

Boolean oos_step(OosVars *gv)
{
    oos_messages_free(gv);
    gv->cycle++;
    generate_messages(gv);
    oos_model_process_stop_messages(gv);
    if (!gv->stopped) {
        update_states(gv);
    }
    return(!gv->stopped);
}

void oos_step_block(OosVars *gv)
{
    gv->block++;
    gv->stopped = FALSE;
    oos_component_initialise_states(gv);
}

void oos_initialise_trial(OosVars *gv)
{
    gv->cycle = 0;
    gv->stopped = FALSE;
}

void oos_initialise_session(OosVars *gv)
{
    gv->cycle = 0;
    gv->block = 0;
    gv->trials_per_subject = 100;     // Up to MAX_TRIALS
    gv->subjects_per_experiment = 36; // Up to MAX_SUBJECTS
    // gv->subjects_per_experiment = 4;  // NS - only to make DEBUG output more manageable
    gv->stopped = FALSE;
}

/******************************************************************************/
/* EXTRANEOUS FUNCTIONS (SHOULD BE DEFINED ELSEWHERE) *************************/

void gtkx_warn(int warn, char *buffer)
{
    fprintf(stdout, "WARNING %d: %s\n", warn, buffer);
}

void pl_error_syntax(char *error_message)
{
    fprintf(stdout, "SYNTAX ERROR: %s\n", error_message);
}

/******************************************************************************/

int oos_count_buffer_elements(OosVars *gv, int id)
{
    BoxList *this = oos_locate_box_ptr(gv, id);

    if (this != NULL) {
        return(timestamped_clause_list_length(this->content));
    }
    else {
        return(-1);
    }
}

/******************************************************************************/
