/*******************************************************************************

    File:     xrng.c
    Author:   Rick Cooper
    Created:  22/06/12
    Edited:   22/06/12
    Contents: An X interface to the RNG model

    Public procedures:
        int main(int argc, char **argv)

*******************************************************************************/
#include "xrng.h"

/* included in xrng.h */
//  #include "rng_subject_data.h"

/******************************************************************************/
/* Section 1: Main -----------------------------------------------------------*/

int main(int argc, char **argv)
{
    OosVars *gv;
    XGlobals xg = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, TRUE, TRUE, FALSE, CANVAS_SECOND_ORDER, CANVAS_VARY_THRESHOLD, {10.0, 1.0, 1.0, 0.0, 8, {0.35, 0.24, 0.12, -0.10, 0.87}}, -1, {}, {}, NULL};
    



    gtk_set_locale();
    gtk_init(&argc, &argv);

    if ((gv = oos_globals_create()) == NULL) {
        fprintf(stdout, "ABORTING: Cannot allocate global variable space\n");
    }
    else if (!rng_create(gv, &(xg.params))) {
        fprintf(stdout, "ABORTING: Cannot create RNG\n");
    }
    else if (!rng_widgets_create(&xg, gv)) {
        fprintf(stderr, "%s: Aborting - Widget creation failed\n", argv[0]);
    }
    else {
        gv->random_generator = gaussian_random_generator_create();
        rng_initialise_model(gv);
        gtk_widget_show(xg.window);
        gtk_main();
    }

    rng_globals_destroy((RngData *)gv->task_data);
    oos_globals_destroy(gv);

    exit(0);
}

/******************************************************************************/
