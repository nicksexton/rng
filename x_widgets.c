/*******************************************************************************

    File:     x_widgets.c
    Author:   Rick Cooper
    Created:  22/06/12
    Edited:   22/06/12
    Contents: An X interface to the RNG model

    Public procedures:
        Boolean rng_widgets_create(XGlobals *globals, OosVars *gv);
        void rng_widgets_initialise(XGlobals *globals);

*******************************************************************************/

#include "xrng.h"
#include "lib_cairox.h"
#include <ctype.h>
#include <cairo-pdf.h>
#include "rng_subject_data.h"


#define NUMBER_OF_METRICS 6
#define Y_SCALE 0.5

// #include "rng_subject_data_jahanshahi2000.h"

// char *stat_label[4] = {"R", "RNG", "TPI", "RG"};
char *stat_label[NUMBER_OF_METRICS] = {"R", "RNG", "RG", "CS1", "CS2", "CST"};

extern RngScores reference_montecarlo_means, reference_montecarlo_sd;

/******************************************************************************/

static void cairo_table_row_headings(cairo_t *cr, PangoLayout *layout, double x0, double y0, double dy)
{
    CairoxTextParameters p;
    // char buffer[32];
    double y;
    int i;

    y = y0;
    for (i = 0; i < NUMBER_OF_METRICS; i++) {
        cairox_text_parameters_set(&p, x0+5, y+dy-2, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
        cairox_paint_pango_text(cr, &p, layout, stat_label[i]);
        cairo_move_to(cr, x0, y);
        cairo_line_to(cr, x0, y+dy);
        cairo_line_to(cr, x0+100, y+dy);
        cairo_line_to(cr, x0+100, y);
        cairo_line_to(cr, x0, y);
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_stroke(cr);
        y += dy;
    }

    /* associates commented for now to simplify table */
    /*
      /
    for (i = 0; i < 10; i++) {
        g_snprintf(buffer, 32, "Associate[+%d]", i);
        cairox_text_parameters_set(&p, x0+5, y+dy-2, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
        cairox_paint_pango_text(cr, &p, layout, buffer);
        cairo_move_to(cr, x0, y);
        cairo_line_to(cr, x0, y+dy);
        cairo_line_to(cr, x0+100, y+dy);
        cairo_line_to(cr, x0+100, y);
        cairo_line_to(cr, x0, y);
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_stroke(cr);
        y += dy;
    
    }
    */
}

static void cairo_table_column(cairo_t *cr, PangoLayout *layout, double x0, double y0, double dy, char *heading, RngScores *means)
{
    CairoxTextParameters p;
    char buffer[32];
    double y;
    // int i;

    y = y0;

    cairox_text_parameters_set(&p, x0+40, y-2, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, heading);

    g_snprintf(buffer, 32, "%5.3f", means->r);
    cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    cairo_move_to(cr, x0, y);
    cairo_line_to(cr, x0, y+dy);
    cairo_line_to(cr, x0+80, y+dy);
    cairo_line_to(cr, x0+80, y);
    cairo_line_to(cr, x0, y);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
    y += dy;

    g_snprintf(buffer, 32, "%5.3f", means->rng);
    cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    cairo_move_to(cr, x0, y);
    cairo_line_to(cr, x0, y+dy);
    cairo_line_to(cr, x0+80, y+dy);
    cairo_line_to(cr, x0+80, y);
    cairo_line_to(cr, x0, y);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
    y += dy;

    /*  // comment TPI
    g_snprintf(buffer, 32, "%5.3f", means->tpi);
    cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    cairo_move_to(cr, x0, y);
    cairo_line_to(cr, x0, y+dy);
    cairo_line_to(cr, x0+80, y+dy);
    cairo_line_to(cr, x0+80, y);
    cairo_line_to(cr, x0, y);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
    y += dy;
     */

    g_snprintf(buffer, 32, "%5.3f", means->rg);
    cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    cairo_move_to(cr, x0, y);
    cairo_line_to(cr, x0, y+dy);
    cairo_line_to(cr, x0+80, y+dy);
    cairo_line_to(cr, x0+80, y);
    cairo_line_to(cr, x0, y);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
    y += dy;


    g_snprintf(buffer, 32, "%5.3f", means->cs1);
    cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    cairo_move_to(cr, x0, y);
    cairo_line_to(cr, x0, y+dy);
    cairo_line_to(cr, x0+80, y+dy);
    cairo_line_to(cr, x0+80, y);
    cairo_line_to(cr, x0, y);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
    y += dy;

    g_snprintf(buffer, 32, "%5.3f", means->cs2);
    cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    cairo_move_to(cr, x0, y);
    cairo_line_to(cr, x0, y+dy);
    cairo_line_to(cr, x0+80, y+dy);
    cairo_line_to(cr, x0+80, y);
    cairo_line_to(cr, x0, y);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
    y += dy;

    g_snprintf(buffer, 32, "%5.3f", means->cst);
    cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    cairo_move_to(cr, x0, y);
    cairo_line_to(cr, x0, y+dy);
    cairo_line_to(cr, x0+80, y+dy);
    cairo_line_to(cr, x0+80, y);
    cairo_line_to(cr, x0, y);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);
    y += dy;


    /* comment associates for now */
    /*
    for (i = 0; i < 10; i++) {
        g_snprintf(buffer, 32, "%5.3f", means->associates[i]);
        cairox_text_parameters_set(&p, x0+60, y+dy-2, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_BOTTOM, 0.0);
        cairox_paint_pango_text(cr, &p, layout, buffer);
        cairo_move_to(cr, x0, y);
        cairo_line_to(cr, x0, y+dy);
        cairo_line_to(cr, x0+80, y+dy);
        cairo_line_to(cr, x0+80, y);
        cairo_line_to(cr, x0, y);
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_stroke(cr);
        y += dy;
    }
    */



}

static void cairo_draw_table(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, OosVars *gv, XGlobals *globals)
{
    RngData *task_data = (RngData *)gv->task_data;
    double dy = (y1 - y0) / 14.0;

    pangox_layout_set_font_size(layout, 12);
    cairo_table_row_headings(cr, layout, x0, y0, dy);

    double x_column_offset = 100;
    double x_column_width = 80;
    

    cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "Ctrl", 
		       &(globals->current_data_set->subject_ctl_means));

    x_column_offset += x_column_width;
    
    if (globals->current_data_set->subject_c6_means.display_if_true) {
      cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "cndn 6", 
			 &(globals->current_data_set->subject_c6_means));
      x_column_offset += x_column_width;
    }


    if (globals->current_data_set->subject_c5_means.display_if_true) {
      cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "cndn 5", 
			 &(globals->current_data_set->subject_c5_means)); 
      x_column_offset += x_column_width;
    }


    if (globals->current_data_set->subject_c4_means.display_if_true) {
      cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "cndn 4", 
			 &(globals->current_data_set->subject_c4_means)); 
      x_column_offset += x_column_width;
    }

    if (globals->current_data_set->subject_c3_means.display_if_true) {
      cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "cndn 3", 
			 &(globals->current_data_set->subject_c3_means));
      x_column_offset += x_column_width;
    }

    if (globals->current_data_set->subject_c2_means.display_if_true) {
      cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "cndn 2", 
			 &(globals->current_data_set->subject_c2_means));
      x_column_offset += x_column_width;
    }

    if (globals->current_data_set->subject_c1_means.display_if_true) {
      cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "cndn 1", 
			 &(globals->current_data_set->subject_c1_means));
      x_column_offset += x_column_width;
    }
     

    if (task_data->n > 0) {
        cairo_table_column(cr, layout, x0+x_column_offset, y0, dy, "Model", &(task_data->group_means));
	
    }
}

/*----------------------------------------------------------------------------*/

static void draw_bar(cairo_t *cr, double x, double w, double y0, double y, double dy, int colour)
{
    cairo_move_to(cr, x-w*0.5, y0);
    cairo_line_to(cr, x-w*0.5, y);
    cairo_line_to(cr, x+w*0.5, y);
    cairo_line_to(cr, x+w*0.5, y0);

    cairox_select_colour(cr, colour, 1.0);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);

    if (dy > 0) {
        cairox_paint_line(cr, 1.0,  x, y-dy, x, y+dy);
        cairox_paint_line(cr, 1.0,  x-3, y+dy, x+3, y+dy);
        cairox_paint_line(cr, 1.0,  x-3, y-dy, x+3, y-dy);
    }
}

static void global_analysis_draw_data(cairo_t *cr, double x0, double x1, double y0, double y1, double offset, RngScores *scores, RngScores *sd, int n, int colour)
{
    double x, y, dy;
    int w = 10;
    /*
    for (i = 0; i < NUMBER_OF_METRICS; i++) {
        x = x0 + (x1 - x0) * (i + 0.5) / NUMBER_OF_METRICS;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
     */
 
   // x = x0 + (x1-x0) * 0.100 + offset * w;
    if (!(scores->r == 0)) {
      x = x0 + (x1-x0) * (0.5/(NUMBER_OF_METRICS)) + offset * w;
      y = (y0+y1)*0.5 + scores->r * (y0-y1) * Y_SCALE * 0.2;
      if (n > 1) {
        dy = sd->r * (y1-y0) * 0.2 / sqrt(n);
      }
      else {
        dy = 0.0;
      }
      draw_bar(cr, x, w, (y0+y1)*0.5, y, dy, colour);
    }


    // x = x0 + (x1-x0) * 0.100 + offset * w;
    if (!(scores->rng == 0)) {
      x = x0 + (x1-x0) * (1.5/(NUMBER_OF_METRICS)) + offset * w;
      y = (y0+y1)*0.5 + scores->rng * (y0-y1) * Y_SCALE * 0.2;
      if (n > 1) {
        dy = sd->rng * (y1-y0) * 0.2 / sqrt(n);
      }
      else {
        dy = 0.0;
      }
      draw_bar(cr, x, w, (y0+y1)*0.5, y, dy, colour);
    }


    // x = x0 + (x1-x0) * 0.300 + offset * w;
    if (!(scores->rg == 0)) {
      x = x0 + (x1-x0) * (2.5/(NUMBER_OF_METRICS)) + offset * w;
      y = (y0+y1)*0.5 + scores->rg * (y0-y1) * Y_SCALE * 0.2;
      if (n > 1) {
        dy = sd->rg * (y1-y0) * 0.2 / sqrt(n);
      }
      else {
        dy = 0.0;
      }
      draw_bar(cr, x, w, (y0+y1)*0.5, y, dy, colour);
    }

    //    x = x0 + (x1-x0) * 0.500 + offset * w;
    if (!(scores->cs1 == 0)) {
      x = x0 + (x1-x0) * (3.5/(NUMBER_OF_METRICS)) + offset * w;
      y = (y0+y1)*0.5 + scores->cs1 * (y0-y1) * Y_SCALE * 0.2;
      if (n > 1) {
        dy = sd->cs1 * (y1-y0) * 0.2 / sqrt(n);
      }
      else {
        dy = 0.0;
      }
      draw_bar(cr, x, w, (y0+y1)*0.5, y, dy, colour);
    }

    // x = x0 + (x1-x0) * 0.700 + offset * w;
    if (!(scores->cs2 == 0)) {
      x = x0 + (x1-x0) * (4.5/(NUMBER_OF_METRICS)) + offset * w;
      y = (y0+y1)*0.5 + scores->cs2 * (y0-y1) * Y_SCALE * 0.2;
      if (n > 1) {
        dy = sd->cs2 * (y1-y0) * 0.2 / sqrt(n);
      }
      else {
        dy = 0.0;
      }
      draw_bar(cr, x, w, (y0+y1)*0.5, y, dy, colour);
    }


    // x = x0 + (x1-x0) * 0.900 + offset * w;
    if (!(scores->cst == 0)) {
      x = x0 + (x1-x0) * (5.5/(NUMBER_OF_METRICS)) + offset * w;
      y = (y0+y1)*0.5 + scores->cst * (y0-y1) * Y_SCALE * 0.2;
      if (n > 1) {
        dy = sd->cst * (y1-y0) * 0.2 / sqrt(n);
      }
      else {
        dy = 0.0;
      }
      draw_bar(cr, x, w, (y0+y1)*0.5, y, dy, colour);
    }
}

static void global_analysis_draw_key(cairo_t *cr, PangoLayout *layout, double x, double y, char *label, int n, int colour)
{
    CairoxTextParameters p;
    char buffer[32];

    // cairo_rectangle(cr, x-18, y-6, 13, 13);
    cairo_rectangle(cr, x-18, y-6, 13, 13);
    cairox_select_colour(cr, colour, 1.0);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_stroke(cr);

    cairox_text_parameters_set(&p, x, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_CENTER, 0.0);
    g_snprintf(buffer, 32, "%s (N = %d)", label, n);
    cairox_paint_pango_text(cr, &p, layout, buffer);
}

static void cairo_draw_global_analysis(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, OosVars *gv, XGlobals *globals)
{
    // extern RngDataset *current_data_set;
    CairoxTextParameters p;
    RngData *task_data = (RngData *)gv->task_data;
    //    RngScores ds_z, tb_z, gng_z, z_scores;
    RngScores data_c6_z, data_c5_z, data_c4_z, data_c3_z, data_c2_z, data_c1_z, z_scores;
    // RngScores ds_sd, tb_sd, gng_sd, scores_sd;
    RngScores data_c6_sd, data_c5_sd, data_c4_sd, data_c3_sd, data_c2_sd, data_c1_sd, scores_sd;
    char buffer[32];
    double x, y, fit;
    int i;

    // Vertical axis:

    /*
    pangox_layout_set_font_size(layout, 12);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
    for (i = 1; i < 10; i++) {
        y = y1 + (y0 - y1) * i / 10.0;
        cairox_paint_line(cr, 1.0, x0-3, y, x1, y);
        cairox_text_parameters_set(&p, x0-4, y, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_CENTER, 0.0);
        if (i % 2 == 1) {
            g_snprintf(buffer, 32, "%4.2f", (i - 5) * 0.5);
            cairox_paint_pango_text(cr, &p, layout, buffer);
        }
    }

    */

    pangox_layout_set_font_size(layout, 12);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
    for (i = 1; i < 20; i++) {
        y = y1 + (y0 - y1) * i / 20.0;
        cairox_paint_line(cr, 1.0, x0-3, y, x1, y);
        cairox_text_parameters_set(&p, x0-4, y, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_CENTER, 0.0);
        if (i % 2 == 1) {
            g_snprintf(buffer, 32, "%4.2f", (i - 10) * 0.5);
            cairox_paint_pango_text(cr, &p, layout, buffer);
        }
    }

    // Horizontal axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < NUMBER_OF_METRICS; i++) {
        x = x0 + (x1 - x0) * (i + 0.5) / NUMBER_OF_METRICS;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
        cairox_text_parameters_set(&p, x, y1+4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
        cairox_paint_pango_text(cr, &p, layout, stat_label[i]);
    }

    /* 
    rng_scores_convert(&subject_ds_means, &ds_z);
    rng_sd_convert(&subject_ds_sd, &ds_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1, -1.5, &ds_z, &ds_sd, 36, 2);
    global_analysis_draw_key(cr, layout, x1-100, y0+10, "DS", 36, 2);

    rng_scores_convert(&subject_2b_means, &tb_z);
    rng_sd_convert(&subject_2b_sd, &tb_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1, -0.5, &tb_z, &tb_sd, 36, 3);
    global_analysis_draw_key(cr, layout, x1-100, y0+30, "2B", 36, 3);

    rng_scores_convert(&subject_gng_means, &gng_z);
    rng_sd_convert(&subject_gng_sd, &gng_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1,  0.5, &gng_z, &gng_sd, 36, 4);
    global_analysis_draw_key(cr, layout, x1-100, y0+50, "GNG", 36, 4);
    */

    /* add in option to only draw data for which flags have been set */

    if (globals->current_data_set->subject_c6_means.display_if_true) {
      rng_scores_convert(&(globals->current_data_set->subject_c6_means), 
			 &(globals->current_data_set->subject_ctl_means), 
			 &(globals->current_data_set->subject_ctl_sd), &data_c6_z);
      rng_sd_convert(&(globals->current_data_set->subject_c6_sd), 
		     &(globals->current_data_set->subject_ctl_sd), &data_c6_sd);
      global_analysis_draw_data(cr, x0, x1, y0, y1, -2.5, &data_c6_z, &data_c6_sd, 36, 2);
      global_analysis_draw_key(cr, layout, x1-100, y0+10, "cndn 6", 36, 2);
    }

    if (globals->current_data_set->subject_c5_means.display_if_true) {
    rng_scores_convert(&(globals->current_data_set->subject_c5_means), 
		       &(globals->current_data_set->subject_ctl_means), 
		       &(globals->current_data_set->subject_ctl_sd), &data_c5_z);
    rng_sd_convert(&(globals->current_data_set->subject_c5_sd), 
		   &(globals->current_data_set->subject_ctl_sd), &data_c5_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1, -1.5, &data_c5_z, &data_c5_sd, 36, 3);
    global_analysis_draw_key(cr, layout, x1-100, y0+30, "cndn 5", 36, 3);
    }

    if (globals->current_data_set->subject_c4_means.display_if_true) {
    rng_scores_convert(&(globals->current_data_set->subject_c4_means), 
		       &(globals->current_data_set->subject_ctl_means), 
		       &(globals->current_data_set->subject_ctl_sd), &data_c4_z);
    rng_sd_convert(&(globals->current_data_set->subject_c4_sd), 
		   &(globals->current_data_set->subject_ctl_sd),&data_c4_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1, -0.5, &data_c4_z, &data_c4_sd, 36, 4);
    global_analysis_draw_key(cr, layout, x1-100, y0+50, "cndn 4", 36, 4);
    }

    if (globals->current_data_set->subject_c3_means.display_if_true) {
    rng_scores_convert(&(globals->current_data_set->subject_c3_means), 
		       &(globals->current_data_set->subject_ctl_means), 
		       &(globals->current_data_set->subject_ctl_sd), &data_c3_z);
    rng_sd_convert(&(globals->current_data_set->subject_c3_sd), 
		   &(globals->current_data_set->subject_ctl_sd),&data_c3_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1, 0.5, &data_c3_z, &data_c3_sd, 36, 5);
    global_analysis_draw_key(cr, layout, x1-100, y0+70, "cndn 3", 36, 5);
    }

    if (globals->current_data_set->subject_c2_means.display_if_true) {
    rng_scores_convert(&(globals->current_data_set->subject_c2_means), 
		       &(globals->current_data_set->subject_ctl_means), 
		       &(globals->current_data_set->subject_ctl_sd), &data_c2_z);
    rng_sd_convert(&(globals->current_data_set->subject_c2_sd), 
		   &(globals->current_data_set->subject_ctl_sd),&data_c2_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1, 1.5, &data_c2_z, &data_c2_sd, 36, 6);
    global_analysis_draw_key(cr, layout, x1-100, y0+90, "cndn 2", 36, 6);
    }

    if (globals->current_data_set->subject_c1_means.display_if_true) {
    rng_scores_convert(&(globals->current_data_set->subject_c1_means), 
		       &(globals->current_data_set->subject_ctl_means), 
		       &(globals->current_data_set->subject_ctl_sd), &data_c1_z);
    rng_sd_convert(&(globals->current_data_set->subject_c1_sd), 
		   &(globals->current_data_set->subject_ctl_sd),&data_c1_sd);
    global_analysis_draw_data(cr, x0, x1, y0, y1, 2.5, &data_c1_z, &data_c1_sd, 36, 7);
    global_analysis_draw_key(cr, layout, x1-100, y0+110, "cndn 1", 36, 7);
    }


    /* Only draw the model data and fits if it has been analysed: */
    if (task_data->n > 0) {
        rng_scores_convert(&(task_data->group_means), 
			   &(globals->current_data_set->subject_ctl_means), 
			   &(globals->current_data_set->subject_ctl_sd), &z_scores);
        rng_sd_convert(&(task_data->group_sd), 
		       &(globals->current_data_set->subject_ctl_sd), &scores_sd);
        global_analysis_draw_data(cr, x0, x1, y0, y1,  3.5, &z_scores, &scores_sd, task_data->n, 6);
        global_analysis_draw_key(cr, layout, x1-100, y0+130, "Model", task_data->n, 6);

	/*

        y = y1 - 100;
        fit = rng_global_fit_max(&(task_data->group_means), &subject_ctl_means);
        cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
        g_snprintf(buffer, 32, "Fit: %5.3f (ctrl)", fit);
        cairox_paint_pango_text(cr, &p, layout, buffer);

        y += 20;
        fit = rng_global_fit_max(&(task_data->group_means), &subject_ds_means);
        cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
        g_snprintf(buffer, 32, "Fit: %5.3f (DS)", fit);
        cairox_paint_pango_text(cr, &p, layout, buffer);

        y += 20;
        fit = rng_global_fit_max(&(task_data->group_means), &subject_2b_means);
        cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
        g_snprintf(buffer, 32, "Fit: %5.3f (2B)", fit);
        cairox_paint_pango_text(cr, &p, layout, buffer);

        y += 20;
        fit = rng_global_fit_max(&(task_data->group_means), &subject_gng_means);
        cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
        g_snprintf(buffer, 32, "Fit: %5.3f (GNG)", fit);
        cairox_paint_pango_text(cr, &p, layout, buffer);

	*/

	y = y1 - 100;
	if (globals->current_data_set->subject_c6_means.display_if_true) {
	  fit = rng_global_fit_max(&(globals->current_data_set->subject_c6_means),
				   &(globals->current_data_set->subject_ctl_sd), 
				   &(task_data->group_means));
	  cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
	  g_snprintf(buffer, 32, "Fit: %5.3f (cndn 6)", fit);
	  cairox_paint_pango_text(cr, &p, layout, buffer);
	}

	if (globals->current_data_set->subject_c5_means.display_if_true) {
	  y += 20;
	  fit = rng_global_fit_max(&(globals->current_data_set->subject_c5_means),
				   &(globals->current_data_set->subject_ctl_sd), 
				   &(task_data->group_means));
	  cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
	  g_snprintf(buffer, 32, "Fit: %5.3f (cndn 5)", fit);
	  cairox_paint_pango_text(cr, &p, layout, buffer);
	}

	if (globals->current_data_set->subject_c4_means.display_if_true) {
	  y += 20;
	  fit = rng_global_fit_max(&(globals->current_data_set->subject_c4_means),
				   &(globals->current_data_set->subject_ctl_sd), 
				     &(task_data->group_means));
	  cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
	  g_snprintf(buffer, 32, "Fit: %5.3f (cndn 4)", fit);
	  cairox_paint_pango_text(cr, &p, layout, buffer);
	}
	  
	if (globals->current_data_set->subject_c3_means.display_if_true) {
	  y += 20;
	  fit = rng_global_fit_max(&(globals->current_data_set->subject_c3_means),
				   &(globals->current_data_set->subject_ctl_sd), 
				     &(task_data->group_means));
	  cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
	  g_snprintf(buffer, 32, "Fit: %5.3f (cndn 3)", fit);
	  cairox_paint_pango_text(cr, &p, layout, buffer);
	}

	if (globals->current_data_set->subject_c2_means.display_if_true) {
	  y += 20;
	  fit = rng_global_fit_max(&(globals->current_data_set->subject_c2_means),
				   &(globals->current_data_set->subject_ctl_sd), 
				   &(task_data->group_means));
	  cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
	  g_snprintf(buffer, 32, "Fit: %5.3f (cndn 2)", fit);
	  cairox_paint_pango_text(cr, &p, layout, buffer);
	}

	if (globals->current_data_set->subject_c1_means.display_if_true) {
	  y += 20;
	  fit = rng_global_fit_max(&(globals->current_data_set->subject_c1_means),
				   &(globals->current_data_set->subject_ctl_sd), 
				     &(task_data->group_means));
	  cairox_text_parameters_set(&p, x0+10, y, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
	  g_snprintf(buffer, 32, "Fit: %5.3f (cndn 1)", fit);
	  cairox_paint_pango_text(cr, &p, layout, buffer);
	}

    }

    /* Outside box, and zero horizontal axis: */
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairox_paint_line(cr, 1.0, x0, y0, x1, y0);
    cairox_paint_line(cr, 1.0, x0, y0, x0, y1);
    cairox_paint_line(cr, 1.0, x1, y1, x0, y1);
    cairox_paint_line(cr, 1.0, x1, y1, x1, y0);
    cairox_paint_line(cr, 1.0, x0, (y1+y0)*0.5, x1, (y1+y0)*0.5);
}

/*----------------------------------------------------------------------------*/

static void cairo_draw_second_order_stats(cairo_t *cr, double x0, double x1, double y0, double y1, RngScores *scores, RngScores *sd, int n, double offset, int colour)
{
    double x, y, dy;
    int k;
    int w = 9;

    /* NS k < 21 
     y0 - y1 is height of graph
    y0 is top of graph */

    for (k = 0; k < 19; k++) {
        x = x0 + (x1 - x0) * (k + 0.5) / 19.0;
        y = y1 + (y0 - y1) * (scores->associates[k] / 0.20); // NS 0.3 is scale of y axis
        if (n > 1) {
            dy = (y1 - y0) * (sd->associates[k] / 0.20) / sqrt(n); // Convert SD to SE
        }
        else {
            dy = 0;
        }
        draw_bar(cr, x+offset*w, w, y1, y, dy, colour);
    }
}

static void cairo_draw_second_order_stats_linegraph(cairo_t *cr, double x0, double x1, double y0, double y1, RngScores *scores, RngScores *sd, int n, double offset, int colour)
{
  double x, y; 
  int k;
  

  cairo_set_line_width (cr, 2);
  cairox_select_colour(cr, colour, 1.0);
    
    for (k = 0; k < 19; k++) {
        x = x0 + (x1 - x0) * (k + 0.5) / 19.0;
        y = y1 + (y0 - y1) * (scores->associates[k] / 0.20); // NS 0.3 is scale of y axis

	if (k == 0) {
	  cairo_move_to (cr, x, y);
	}
	else {
	  cairo_line_to (cr, x, y);

	  /* Draw error bars here */

        }

    }
	cairo_stroke (cr);
}




static void cairo_draw_second_order_analysis(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, OosVars *gv, XGlobals *globals)
{
  // extern RngDataset *current_data_set;
    CairoxTextParameters p;
    RngData *task_data = (RngData *)gv->task_data;
    char buffer[16];
    double x, y;
    int i;

    cairox_paint_line(cr, 1.0, x0, y0, x1, y0);
    cairox_paint_line(cr, 1.0, x0, y0, x0, y1);
    cairox_paint_line(cr, 1.0, x1, y1, x0, y1);
    cairox_paint_line(cr, 1.0, x1, y1, x1, y0);

    // Vertical axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < 9; i++) {
        y = y1 + (y0 - y1) * i / 8.0;
        cairox_paint_line(cr, 1.0, x0-3, y, x0+3, y);
        cairox_text_parameters_set(&p, x0-4, y, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_CENTER, 0.0);
        g_snprintf(buffer, 16, "%4.2f", i * (0.2/8)); // scale
        cairox_paint_pango_text(cr, &p, layout, buffer);
    }
    cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
    y = y1 + (y0 - y1) * 2 / 8.0; // Horizontal line at 0.05
    cairox_paint_line(cr, 1.0, x0, y, x1, y);
    y = y1 + (y0 - y1) * 4 / 8.0; // Horizontal line at 0.10
    cairox_paint_line(cr, 1.0, x0, y, x1, y);
    y = y1 + (y0 - y1) * 6 / 8.0; // Horizontal line at 0.15
    cairox_paint_line(cr, 1.0, x0, y, x1, y);


    /* Change so towse analysis goes from 1 - 21 */
    // Horizontal axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < 19; i++) {
        x = x0 + (x1 - x0) * (i + 0.5) / 19.0;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
        cairox_text_parameters_set(&p, x, y1+4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
        if (i < 9) {
	  /* needs to be if i < 10 */
            g_snprintf(buffer, 16, "-%d", 9 - i);
        }
        else if (i > 9) {
            g_snprintf(buffer, 16, "+%d", i - 9);
        }
        else {
            g_snprintf(buffer, 16, "0");
        }
        cairox_paint_pango_text(cr, &p, layout, buffer);
    }


    if (globals->current_data_set->subject_c3_means.display_if_true) {
    cairo_draw_second_order_stats_linegraph(cr, x0, x1, y0, y1, &(globals->current_data_set->subject_c3_means),
				  &(globals->current_data_set->subject_c3_sd), 26, -2, 0);
    global_analysis_draw_key(cr, layout, x1-100, y0+10, "cndn 3", 36, 0);
    }
    
    if (globals->current_data_set->subject_c2_means.display_if_true) {
    cairo_draw_second_order_stats_linegraph(cr, x0, x1, y0, y1, &(globals->current_data_set->subject_c2_means), 
				  &(globals->current_data_set->subject_c2_sd), 36, -1, 2);
    global_analysis_draw_key(cr, layout, x1-100, y0+30, "cndn 2", 36, 2);
    }

    if (globals->current_data_set->subject_c1_means.display_if_true) {
    cairo_draw_second_order_stats_linegraph(cr, x0, x1, y0, y1, &(globals->current_data_set->subject_c1_means), 
				  &(globals->current_data_set->subject_c1_sd), 36, 0, 3);
    global_analysis_draw_key(cr, layout, x1-100, y0+50, "cndn 1", 36, 3);
    }



    if (task_data->n > 0) {
        cairo_draw_second_order_stats(cr, x0, x1, y0, y1, &(task_data->group_means), &(task_data->group_sd), task_data->n, 0, 6);
        global_analysis_draw_key(cr, layout, x1-100, y0+90, "Model", task_data->n, 6);
    }
}

/*----------------------------------------------------------------------------*/
/* ----------------- PARAMETER STUDY DRAW LINES ----------------------------- */
static void cairo_draw_varied_data(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, XGlobals *globals)
{
    CairoxTextParameters p;
    char buffer[16];
    double x, y, dy;
    int i;

    // Vertical axis
    pangox_layout_set_font_size(layout, 12);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
    for (i = 1; i < 10; i++) {
        y = y1 + (y0 - y1) * i / 10.0;
        cairox_paint_line(cr, 1.0, x0-3, y, x1, y);
        cairox_text_parameters_set(&p, x0-4, y, PANGOX_XALIGN_RIGHT, PANGOX_YALIGN_CENTER, 0.0);
        if (i % 2 == 1) {
            g_snprintf(buffer, 32, "%4.2f", (i - 5) * 0.5);
            cairox_paint_pango_text(cr, &p, layout, buffer);
        }
    }
    /*
    // Draw the data for R: First the legend...
    cairox_text_parameters_set(&p, x1-350, y0+20, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, "R");
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    cairox_paint_line(cr, 2, x1-370, y0+15, x1-355, y0+15);
    if (globals->group_index >= 0) {
        // Draw the data for R: Then the line...
        x = x0 + 10;
        y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[0].r / 5.00;
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, x, y);
        for (i = 1; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].r / 5.00;
            cairo_line_to(cr, x, y);
        }
        cairo_stroke(cr);
        cairo_set_line_width(cr, 1.0);
        // Draw the data for R: Then the error bars...
        for (i = 0; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].r / 5.00;
            dy = (y0 - y1) * globals->group_sd[i].r / 6.0 / 5.00;
            cairox_paint_line(cr, 1.0, x, y-dy, x, y+dy);
            cairox_paint_line(cr, 1.0, x-3, y-dy, x+3, y-dy);
            cairox_paint_line(cr, 1.0, x-3, y+dy, x+3, y+dy);
        }
    }
    */


    // Draw the data for RNG: First the legend...
    cairox_text_parameters_set(&p, x1-350, y0+20, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, "RNG");
    cairo_set_source_rgb(cr, 0.2, 0.8, 0.2);
    cairox_paint_line(cr, 2, x1-370, y0+15, x1-355, y0+15);
    if (globals->group_index >= 0) {
        // Draw the data for RNG: Then the line...
        x = x0 + 10;
        y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[0].rng / 5.00;
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, x, y);
        for (i = 1; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].rng / 5.00;
            cairo_line_to(cr, x, y);
        }
        cairo_stroke(cr);
        cairo_set_line_width(cr, 1.0);
        // Draw the data for RNG: Then the error bars...
        for (i = 0; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].rng / 5.00;
            dy = (y0 - y1) * globals->group_sd[i].rng / 6.0 / 5.00;
            cairox_paint_line(cr, 1.0, x, y-dy, x, y+dy);
            cairox_paint_line(cr, 1.0, x-3, y-dy, x+3, y-dy);
            cairox_paint_line(cr, 1.0, x-3, y+dy, x+3, y+dy);
        }
    }

    /*
    // Draw the data for TPI: First the legend...
    cairox_text_parameters_set(&p, x1-150, y0+20, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, "TPI");
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    cairox_paint_line(cr, 2, x1-170, y0+15, x1-155, y0+15);
    if (globals->group_index >= 0) {
        // Draw the data for TPI: Then the line...
        x = x0 + 10;
        y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[0].tpi / 5.00;
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, x, y);
        for (i = 1; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].tpi / 5.00;
            cairo_line_to(cr, x, y);
        }
        cairo_stroke(cr);
        cairo_set_line_width(cr, 1.0);
        // Draw the data for TPI: Then the error bars...
        for (i = 0; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].tpi / 5.00;
            dy = (y0 - y1) * globals->group_sd[i].tpi / 6.0 / 5.00;
            cairox_paint_line(cr, 1.0, x, y-dy, x, y+dy);
            cairox_paint_line(cr, 1.0, x-3, y-dy, x+3, y-dy);
            cairox_paint_line(cr, 1.0, x-3, y+dy, x+3, y+dy);
        }
    }
    */


    // Draw the data for CST: First the legend...
    cairox_text_parameters_set(&p, x1-250, y0+20, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, "CST");
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    cairox_paint_line(cr, 2, x1-270, y0+15, x1-255, y0+15);
    if (globals->group_index >= 0) {
        // Draw the data for CST: Then the line...
        x = x0 + 10;
        y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[0].cst / 5.00;
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, x, y);
        for (i = 1; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].cst / 5.00;
            cairo_line_to(cr, x, y);
        }
        cairo_stroke(cr);
        cairo_set_line_width(cr, 1.0);
        // Draw the data for CST: Then the error bars...
        for (i = 0; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].cst / 5.00;
            dy = (y0 - y1) * globals->group_sd[i].cst / 6.0 / 5.00;
            cairox_paint_line(cr, 1.0, x, y-dy, x, y+dy);
            cairox_paint_line(cr, 1.0, x-3, y-dy, x+3, y-dy);
            cairox_paint_line(cr, 1.0, x-3, y+dy, x+3, y+dy);
        }
    }

    // Draw the data for CS1: First the legend...
    cairox_text_parameters_set(&p, x1-150, y0+20, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, "CS1");
    cairo_set_source_rgb(cr, 0.0, 0.4, 1.0);
    cairox_paint_line(cr, 2, x1-170, y0+15, x1-155, y0+15);
    if (globals->group_index >= 0) {
        // Draw the data for CS1: Then the line...
        x = x0 + 10;
        y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[0].cs1 / 5.00;
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, x, y);
        for (i = 1; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].cs1 / 5.00;
            cairo_line_to(cr, x, y);
        }
        cairo_stroke(cr);
        cairo_set_line_width(cr, 1.0);
        // Draw the data for CS1: Then the error bars...
        for (i = 0; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].cs1 / 5.00;
            dy = (y0 - y1) * globals->group_sd[i].cs1 / 6.0 / 5.00;
            cairox_paint_line(cr, 1.0, x, y-dy, x, y+dy);
            cairox_paint_line(cr, 1.0, x-3, y-dy, x+3, y-dy);
            cairox_paint_line(cr, 1.0, x-3, y+dy, x+3, y+dy);
        }
    }




    // Draw the data for RG: First the legend...
    cairox_text_parameters_set(&p, x1-50, y0+20, PANGOX_XALIGN_LEFT, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, "RG");
    cairo_set_source_rgb(cr, 1.0, 0.2, 1.0);
    cairox_paint_line(cr, 2, x1-70, y0+15, x1-55, y0+15);
    if (globals->group_index >= 0) {
        // Draw the data for RG: Then the line...
        x = x0 + 10;
        y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[0].rg / 5.00;
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, x, y);
        for (i = 1; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].rg / 5.00;
            cairo_line_to(cr, x, y);
        }
        cairo_stroke(cr);
        cairo_set_line_width(cr, 1.0);
        // Draw the data for RG: Then the error bars...
        for (i = 0; i < globals->group_index; i++) {
            x = x0 + 10 + (x1 - x0 - 20) *  i / (MAX_GROUPS - 1.0);
            y = (y0 + y1) * 0.5 + (y0 - y1) * globals->group_mean[i].rg / 5.00;
            dy = (y0 - y1) * globals->group_sd[i].rg / 6.0 / 5.00;
            cairox_paint_line(cr, 1.0, x, y-dy, x, y+dy);
            cairox_paint_line(cr, 1.0, x-3, y-dy, x+3, y-dy);
            cairox_paint_line(cr, 1.0, x-3, y+dy, x+3, y+dy);
        }
    }



    

    // Outside box, and zero horizontal axis:
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairox_paint_line(cr, 1.0, x0, y0, x1, y0);
    cairox_paint_line(cr, 1.0, x0, y0, x0, y1);
    cairox_paint_line(cr, 1.0, x1, y1, x0, y1);
    cairox_paint_line(cr, 1.0, x1, y1, x1, y0);
    cairox_paint_line(cr, 1.0, x0, (y1+y0)*0.5, x1, (y1+y0)*0.5);
}

/*----------------------------------------------------------------------------*/

static void cairo_draw_vary_period_axis(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, XGlobals *globals)
{
    CairoxTextParameters p;
    char buffer[16];
    double x;
    int i;

    // Horizontal axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < 11; i++) {
        x = x0 + 10 + (x1 - x0 - 20) *  i / 10.0;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
        cairox_text_parameters_set(&p, x, y1+4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
        g_snprintf(buffer, 16, "%d", 4 + (i * 2)); // period axis
        cairox_paint_pango_text(cr, &p, layout, buffer);
    }
}

static void cairo_draw_vary_threshold_axis(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, XGlobals *globals)
{
    CairoxTextParameters p;
    char buffer[16];
    double x;
    int i;

    // Horizontal axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < 11; i++) {
        x = x0 + 10 + (x1 - x0 - 20) *  i / 10.0;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
        cairox_text_parameters_set(&p, x, y1+4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
        g_snprintf(buffer, 16, "%4.2f", -0.5 + (i * 0.1));
        cairox_paint_pango_text(cr, &p, layout, buffer);
    }
}

static void cairo_draw_vary_update_axis(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, XGlobals *globals)
{
    CairoxTextParameters p;
    char buffer[16];
    double x;
    int i;

    // Horizontal axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < 11; i++) {
        x = x0 + 10 + (x1 - x0 - 20) *  i / 10.0;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
        cairox_text_parameters_set(&p, x, y1+4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
        g_snprintf(buffer, 16, "%4.2f", 1.0 - (i * 0.1));
        cairox_paint_pango_text(cr, &p, layout, buffer);
    }
}

static void cairo_draw_vary_monitoring_axis(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, XGlobals *globals)
{
    CairoxTextParameters p;
    char buffer[16];
    double x;
    int i;

    // Horizontal axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < 11; i++) {
        x = x0 + 10 + (x1 - x0 - 20) *  i / 10.0;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
        cairox_text_parameters_set(&p, x, y1+4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
        g_snprintf(buffer, 16, "%4.2f", 1.0 - (i * 0.1));
        cairox_paint_pango_text(cr, &p, layout, buffer);
    }
}

static void cairo_draw_vary_temperature_axis(cairo_t *cr, PangoLayout *layout, double x0, double x1, double y0, double y1, XGlobals *globals)
{
    CairoxTextParameters p;
    char buffer[16];
    double x;
    int i;

    // Horizontal axis
    pangox_layout_set_font_size(layout, 12);
    for (i = 0; i < 11; i++) {
        x = x0 + 10 + (x1 - x0 - 20) *  i / 10.0;
        cairox_paint_line(cr, 1.0, x, y1-3, x, y1+3);
        cairox_text_parameters_set(&p, x, y1+4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_TOP, 0.0);
        g_snprintf(buffer, 16, "%d", i * 10);
        cairox_paint_pango_text(cr, &p, layout, buffer);
    }
}

/*----------------------------------------------------------------------------*/

static void cairo_draw_results_analysis(cairo_t *cr, XGlobals *globals, int width, int height)
{
    PangoLayout *layout;

    if (globals->running) {
        cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
    }
    else {
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    }
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    layout = pango_cairo_create_layout(cr);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

    switch (globals->canvas1_selection) {
        case CANVAS_TABLE: {
	  /* adjusting layout
	  cairo_draw_table(cr, layout, (width-500)*0.5, (width+500)*0.5, height*0.15, height*0.85, globals->gv, globals);   */
	  cairo_draw_table(cr, layout, width*0.05, width*0.95, height*0.15, height*0.85, globals->gv, globals);   

            break;
        }
        case CANVAS_GLOBAL: {
	  cairo_draw_global_analysis(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals->gv, globals);
            break;
        }
        case CANVAS_SECOND_ORDER: {
	  cairo_draw_second_order_analysis(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals->gv, globals);
            break;
        }
    }
    g_object_unref(layout);
}

static void x_draw_canvas1(XGlobals *globals)
{
    if (globals->output_panel1 != NULL) {
        cairo_surface_t *s;
        cairo_t *cr;
        int width, height;

        /* Double buffer: First create and draw to a surface: */
        gtk_widget_realize(globals->output_panel1);
        width = globals->output_panel1->allocation.width;
        height = globals->output_panel1->allocation.height;
        s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
        cr = cairo_create(s);
        cairo_draw_results_analysis(cr, globals, width, height);
        cairo_destroy(cr);

        /* Now copy the surface to the window: */
        cr = gdk_cairo_create(globals->output_panel1->window);
        cairo_set_source_surface(cr, s, 0.0, 0.0);
        cairo_paint(cr);
        cairo_destroy(cr);

        /* And destroy the surface: */
        cairo_surface_destroy(s);
    }
}



static void cairo_draw_parameter_analysis(cairo_t *cr, XGlobals *globals, int width, int height)
{
    PangoLayout *layout;
    CairoxTextParameters p;
    char buffer[256];

    if (globals->running) {
        cairo_set_source_rgb(cr, 0.85, 0.85, 0.85);
    }
    else {
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    }
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    layout = pango_cairo_create_layout(cr);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

    switch (globals->canvas2_selection) {
	  /* NS CANVAS_VARY_PERIOD here */
        case CANVAS_VARY_PERIOD: {
            cairo_draw_vary_period_axis(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            cairo_draw_varied_data(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            g_snprintf(buffer, 256, "Gen. Period: variable; WM threshold: %5.3f; Monitoring efficiency: %5.3f; WM update efficiency: %5.3f; Task setting temperature: %d", globals->params.wm_threshold, globals->params.monitoring_efficiency, globals->params.wm_update_rate, (int) globals->params.temperature);
            break;
        }

        case CANVAS_VARY_THRESHOLD: {
            cairo_draw_vary_threshold_axis(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            cairo_draw_varied_data(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            g_snprintf(buffer, 256, "Gen. Period: %d; WM threshold: variable; Mon. effic.: %5.3f; WM update effic.: %5.3f; Task setting temp.: %d", globals->params.generation_period, globals->params.monitoring_efficiency, globals->params.wm_update_rate, (int) globals->params.temperature);
            break;
        }
        case CANVAS_VARY_MONITORING: {
            cairo_draw_vary_monitoring_axis(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            cairo_draw_varied_data(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            g_snprintf(buffer, 256, "Gen. Period: %d; WM threshold: %5.3f; Mon. effic.: variable; WM update effic.: %5.3f; Task setting temp.: %d", globals->params.generation_period, globals->params.wm_threshold, globals->params.wm_update_rate, (int) globals->params.temperature);

            break;
        }
        case CANVAS_VARY_UPDATE: {
            cairo_draw_vary_update_axis(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            cairo_draw_varied_data(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            g_snprintf(buffer, 256, "Gen. Period: %d; WM threshold: %5.3f; Mon. effic.: %5.3f; WM update effic.: variable; Task setting temp.: %d", globals->params.generation_period, globals->params.wm_threshold, globals->params.monitoring_efficiency, (int) globals->params.temperature);

            break;
        }
        case CANVAS_VARY_TEMPERATURE: {
            cairo_draw_vary_temperature_axis(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            cairo_draw_varied_data(cr, layout, width*0.08, width*0.95, height*0.15, height*0.85, globals);
            g_snprintf(buffer, 256, "Gen. Period: %d; WM threshold: %5.3f; Mon. effic.: %5.3f; WM update effic.: %5.3f; Task setting temp.: variable", globals->params.generation_period, globals->params.wm_threshold, globals->params.monitoring_efficiency, globals->params.wm_update_rate);

            break;
        }

    }
    cairox_text_parameters_set(&p, width*0.5, height-4, PANGOX_XALIGN_CENTER, PANGOX_YALIGN_BOTTOM, 0.0);
    cairox_paint_pango_text(cr, &p, layout, buffer);
    g_object_unref(layout);
}

static void x_draw_canvas2(XGlobals *globals)
{
    if (globals->output_panel2 != NULL) {
        cairo_surface_t *s;
        cairo_t *cr;
        int width, height;

        /* Double buffer: First create and draw to a surface: */
        gtk_widget_realize(globals->output_panel2);
        width = globals->output_panel2->allocation.width;
        height = globals->output_panel2->allocation.height;
        s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
        cr = cairo_create(s);
        cairo_draw_parameter_analysis(cr, globals, width, height);
        cairo_destroy(cr);

        /* Now copy the surface to the window: */
        cr = gdk_cairo_create(globals->output_panel2->window);
        cairo_set_source_surface(cr, s, 0.0, 0.0);
        cairo_paint(cr);
        cairo_destroy(cr);

        /* And destroy the surface: */
        cairo_surface_destroy(s);
    }
}

/******************************************************************************/

static void x_task_initialise(GtkWidget *caller, XGlobals *globals)
{
    rng_create(globals->gv, &(globals->params));
    rng_initialise_model(globals->gv);
    x_draw_canvas1(globals);
}

static void x_task_run_block(GtkWidget *caller, XGlobals *globals)
{
    globals->running = TRUE;
    x_draw_canvas1(globals);
    gtk_main_iteration_do(FALSE);
    rng_create(globals->gv, &(globals->params));
    rng_initialise_model(globals->gv);
    rng_run(globals->gv);
    printf ("ts_temp = %4.2f, mon_eff = %4.2f, wm_update_rate = %4.2f, wm_threshold = %4.2f, gen_period = %d\n", 
	    globals->params.temperature, globals->params.monitoring_efficiency, globals->params.wm_update_rate, 
	    globals->params.wm_threshold, globals->params.generation_period);
    rng_analyse_group_data(globals->gv, stdout, &reference_montecarlo_means, &reference_montecarlo_sd);
    globals->running = FALSE;
    x_draw_canvas1(globals);
}

static void set_variable_parameter(XGlobals *globals)
{
    // Note: group_index varies from 0 up to MAX_GROUPS (exclusive)

    if (globals->canvas2_selection == CANVAS_VARY_THRESHOLD) {
      globals->params.wm_threshold = -0.5 + globals->group_index * 0.05;
    }
    else if (globals->canvas2_selection == CANVAS_VARY_MONITORING) {
        globals->params.monitoring_efficiency = 1.0 - globals->group_index * 0.05;
    }
    else if (globals->canvas2_selection == CANVAS_VARY_UPDATE) {
        globals->params.wm_update_rate = 1.0 - globals->group_index * 0.05;
    }
    else if (globals->canvas2_selection == CANVAS_VARY_TEMPERATURE) {
        globals->params.temperature = globals->group_index * 5.0;
    }
    else if (globals->canvas2_selection == CANVAS_VARY_PERIOD) {
      globals->params.generation_period = 4 + globals->group_index * 1;
    }
    /* NS else if CANVAS_VARY_PERIOD here */

}


/*-----------------------------PARAMETER STUDY -------------------------------------*/

static void x_task_run_parameter_study(GtkWidget *caller, XGlobals *globals)
{
    RngData *task_data;
    RngParameters tmp;
    // extern RngDataset *current_data_set;

    globals->running = TRUE;
    x_draw_canvas2(globals);
    gtk_main_iteration_do(FALSE);
    tmp.wm_threshold = globals->params.wm_threshold;
    tmp.monitoring_efficiency = globals->params.monitoring_efficiency;
    tmp.wm_update_rate = globals->params.wm_update_rate;
    tmp.temperature = globals->params.temperature;
    /* NS period here */
    tmp.generation_period = globals->params.generation_period;

    if (globals->current_data_set == NULL)
      {
	printf ("valid subject data set not selected\n");
	return;
      }

    for (globals->group_index = 0; globals->group_index < MAX_GROUPS; globals->group_index++) {
        set_variable_parameter(globals);
        rng_create(globals->gv, &(globals->params));
        rng_initialise_model(globals->gv);
        rng_run(globals->gv);
        rng_analyse_group_data(globals->gv, NULL, &reference_montecarlo_means, &reference_montecarlo_sd);
        task_data = (RngData *)globals->gv->task_data;

	/* Calculate R */
        globals->group_mean[globals->group_index].r = 
	  (task_data->group_means.r - globals->current_data_set->subject_ctl_means.r) / globals->current_data_set->subject_ctl_sd.r;
        globals->group_sd[globals->group_index].r = 
	  task_data->group_sd.r / globals->current_data_set->subject_ctl_sd.r;

	/* Calculate RNG */
        globals->group_mean[globals->group_index].rng = 
	  (task_data->group_means.rng - globals->current_data_set->subject_ctl_means.rng) / globals->current_data_set->subject_ctl_sd.rng;
        globals->group_sd[globals->group_index].rng = 
	  task_data->group_sd.rng / globals->current_data_set->subject_ctl_sd.rng;

	/* Calculate TPI */
	/*
        globals->group_mean[globals->group_index].tpi = 
	  (task_data->group_means.tpi - globals->current_data_set->subject_ctl_means.tpi) / globals->current_data_set->subject_ctl_sd.tpi;
        globals->group_sd[globals->group_index].tpi = 
	  task_data->group_sd.tpi / globals->current_data_set->subject_ctl_sd.tpi;
	*/

	/* Calculate RG */
        globals->group_mean[globals->group_index].rg = 
	  (task_data->group_means.rg - globals->current_data_set->subject_ctl_means.rg) / globals->current_data_set->subject_ctl_sd.rg;
        globals->group_sd[globals->group_index].rg = 
	  task_data->group_sd.rg / globals->current_data_set->subject_ctl_sd.rg;


	/* Calculate CS1 */
        globals->group_mean[globals->group_index].cs1 = 
	  (task_data->group_means.cs1 - globals->current_data_set->subject_ctl_means.cs1) / globals->current_data_set->subject_ctl_sd.cs1;
        globals->group_sd[globals->group_index].cs1 = 
	  task_data->group_sd.cs1 / globals->current_data_set->subject_ctl_sd.cs1;

	/* Calculate CST */
        globals->group_mean[globals->group_index].cst = 
	  (task_data->group_means.cst - globals->current_data_set->subject_ctl_means.cst) / globals->current_data_set->subject_ctl_sd.cst;
        globals->group_sd[globals->group_index].cst = 
	  task_data->group_sd.cst / globals->current_data_set->subject_ctl_sd.cst;




        if (globals->dynamic_canvases) {
            x_draw_canvas2(globals);
        }
        gtk_main_iteration_do(FALSE);
    }

    globals->running = FALSE;
    x_draw_canvas2(globals);
    globals->params.wm_threshold = tmp.wm_threshold;
    globals->params.monitoring_efficiency = tmp.monitoring_efficiency;
    globals->params.wm_update_rate = tmp.wm_update_rate;
    globals->params.temperature = tmp.temperature;
    globals->params.generation_period = tmp.generation_period;
    /* NS params here */
}

static void x_redraw_canvases(GtkWidget *caller, XGlobals *globals)
{
    int page = gtk_notebook_get_current_page(GTK_NOTEBOOK(globals->notebook));

// Alternative to the following is to emit an expose event for the relevant
// canvas (and then process all events?)

    if (page == 0) {
        diagram_draw_x(globals);
    }
    else if (page == 1) {
        browser_draw_x(globals);
    }
    else if (page == 2) {
        x_draw_canvas1(globals);
    }
    else if (page == 3) {
        x_draw_canvas2(globals);
    }
}

static void x_print_canvas(GtkWidget *caller, XGlobals *globals)
{
    cairo_surface_t *surface;
    GtkWidget *da;
    cairo_t *cr;
    int page, width, height;

    page = gtk_notebook_get_current_page(GTK_NOTEBOOK(globals->notebook));

    if (page == 0) {
        da = globals->diagram;
        width = da->allocation.width;
        height = da->allocation.height;

        surface = cairo_pdf_surface_create("screen_dump_architecture.pdf", width, height);
        cr = cairo_create(surface);
        diagram_draw_cairo(cr, globals, width, height);
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    else if (page == 1) {
        da = globals->diagram;
        width = da->allocation.width;
        height = da->allocation.height;

        surface = cairo_pdf_surface_create("screen_dump_browser.pdf", width, height);
        cr = cairo_create(surface);
        browser_draw_cairo(cr, globals->gv, width, height);
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    else if (page == 2) {
        da = globals->output_panel1;
        width = da->allocation.width;
        height = da->allocation.height;

        surface = cairo_pdf_surface_create("screen_dump_results.pdf", width, height);
        cr = cairo_create(surface);
        cairo_draw_results_analysis(cr, globals, width, height);
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
    else if (page == 3) {
        da = globals->output_panel2;
        width = da->allocation.width;
        height = da->allocation.height;

        surface = cairo_pdf_surface_create("screen_dump_parameters.pdf", width, height);
        cr = cairo_create(surface);
        cairo_draw_parameter_analysis(cr, globals, width, height);
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
    }
}

/******************************************************************************/

static int analysis_canvas1_event_expose(GtkWidget *da, GdkEventConfigure *event, XGlobals *globals)
{
    x_draw_canvas1(globals);
    return(1);
}

static int analysis_canvas2_event_expose(GtkWidget *da, GdkEventConfigure *event, XGlobals *globals)
{
    x_draw_canvas2(globals);
    return(1);
}

/*----------------------------------------------------------------------------*/

#if FALSE
static void x_toggle_dynamic_display(GtkWidget *caller, XGlobals *globals)
{
    globals->dynamic_canvases = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller));
}

static void x_toggle_colour(GtkWidget *caller, XGlobals *globals)
{
    globals->colour = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller));
    x_draw_canvas1(globals);
}
#endif

static void radio_select_table(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas1_selection = CANVAS_TABLE;
        x_draw_canvas1(globals);
    }
}

static void radio_select_global_graph(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas1_selection = CANVAS_GLOBAL;
        x_draw_canvas1(globals);
    }
}

static void radio_select_2nd_order_graph(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas1_selection = CANVAS_SECOND_ORDER;
        x_draw_canvas1(globals);
    }
}

void radio_select_dataset_jahanshahi_1998(GtkWidget *caller, XGlobals *globals)
{
  // RngDataset dataset_jahanshahi_1998;
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
    printf ("selecting Jahanshahi 1998 data set\n");
    globals->current_data_set = &dataset_jahanshahi_1998;
  }
}

void radio_select_dataset_jahanshahi_2006(GtkWidget *caller, XGlobals *globals)
{
  // RngDataset dataset_jahanshahi_2006;
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
    printf ("selecting Jahanshahi 2006 data set\n");
    globals->current_data_set = &dataset_jahanshahi_2006;
  }
}

void radio_select_dataset_towse_1998(GtkWidget *caller, XGlobals *globals)
{
  // RngDataset dataset_towse_1998;
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
    printf ("selecting Towse data set\n");
       globals->current_data_set = &dataset_towse_1998;

  }
}




static void x_spin_generation_period(GtkWidget *button, XGlobals *globals)
{
    globals->params.generation_period = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_wm_threshold(GtkWidget *button, XGlobals *globals)
{
    globals->params.wm_threshold = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_monitoring_efficiency(GtkWidget *button, XGlobals *globals)
{
    globals->params.monitoring_efficiency = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_update_rate(GtkWidget *button, XGlobals *globals)
{
    globals->params.wm_update_rate = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_temperature(GtkWidget *button, XGlobals *globals)
{
    globals->params.temperature = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));

    // rng_print_schema_selection_probabilities(stdout, globals->params.temperature);
}
/*
static void x_spin_act_self(GtkWidget *button, XGlobals *globals)
{
    globals->params.activation_parameters.act_self = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_act_next(GtkWidget *button, XGlobals *globals)
{
    globals->params.activation_parameters.act_next = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_act_prev(GtkWidget *button, XGlobals *globals)
{
    globals->params.activation_parameters.act_prev = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_act_inhi(GtkWidget *button, XGlobals *globals)
{
    globals->params.activation_parameters.act_inhi = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));
}

static void x_spin_persistence(GtkWidget *button, XGlobals *globals)
{
    globals->params.activation_parameters.persistence = gtk_spin_button_get_value(GTK_SPIN_BUTTON(button));

}
*/

/*----------------------------------------------------------------------------*/

static gint event_delete(GtkWidget *caller, GdkEvent *event, XGlobals *globals)
{
    return(0);    // Return 1 if we need to abort
}

/*----------------------------------------------------------------------------*/

static void callback_destroy(GtkWidget *caller, XGlobals *globals)
{
    gtk_main_quit();
}

/*----------------------------------------------------------------------------*/

static GtkWidget *notepage_basic_results_create(XGlobals *globals)
{
    GtkWidget *page, *hbox, *hbox_container, *frame, *tmp, *vbox, *align;
    GtkToolItem *tool_item;
    GtkTooltips *tooltips;
    GSList *radio_group = NULL;
    GSList *radio_group_dataset_select = NULL;

    page = gtk_vbox_new(FALSE, 0);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(page), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

    tmp = gtk_label_new("Parameters:");
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    gtk_widget_show(tmp);

    tooltips = gtk_tooltips_new();

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_GOTO_LAST); // Run Block
    g_signal_connect(G_OBJECT(tool_item), "clicked", G_CALLBACK(x_task_run_block), globals);
    gtk_tooltips_set_tip(tooltips, GTK_WIDGET(tool_item), "Run 36 virtual subjects", NULL);
    gtk_box_pack_end(GTK_BOX(hbox), GTK_WIDGET(tool_item), FALSE, FALSE, 5);
    gtk_widget_show(GTK_WIDGET(tool_item));

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_GOTO_FIRST); // Initialise
    g_signal_connect(G_OBJECT(tool_item), "clicked", G_CALLBACK(x_task_initialise), globals);
    gtk_tooltips_set_tip(tooltips, GTK_WIDGET(tool_item), "Re-initialise", NULL);
    gtk_box_pack_end(GTK_BOX(hbox), GTK_WIDGET(tool_item), FALSE, FALSE, 5);
    gtk_widget_show(GTK_WIDGET(tool_item));

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(page), hbox, FALSE, FALSE, 5);
    gtk_widget_show(hbox);

    vbox = gtk_vbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 20);
    gtk_widget_show(vbox);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    /* generation period param */
    tmp = gtk_label_new("Generation Period:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("WM threshold:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("Monitoring efficiency:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("WM update efficiency:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("Task Setting temperature:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    vbox = gtk_vbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 5);
    gtk_widget_show(vbox);

    tmp = gtk_spin_button_new_with_range(4.0, 40.0, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.generation_period);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_generation_period), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(-1.0, 1.0, 0.05);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.wm_threshold);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_wm_threshold), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(0.0, 1.0, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.monitoring_efficiency);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_monitoring_efficiency), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(0.0, 1.0, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.wm_update_rate);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_update_rate), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(0.1, 100.0, 1.0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.temperature);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_temperature), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    /* activation parameters */
    /*
    vbox = gtk_vbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 20);
    gtk_widget_show(vbox);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("Spreading activation weight; self:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("Spreading activation weight; next:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("Spreading activation weight; prev:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("lateral inhibition:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

    align = gtk_alignment_new(0.0, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), align, TRUE, TRUE, 0);
    gtk_widget_show(align);

    tmp = gtk_label_new("Persistence:");
    gtk_container_add(GTK_CONTAINER(align), tmp);
    gtk_widget_show(tmp);

   vbox = gtk_vbox_new(TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), vbox, FALSE, FALSE, 5);
    gtk_widget_show(vbox);
    
    tmp = gtk_spin_button_new_with_range(0.00, 1.00, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.activation_parameters.act_self);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_act_self), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(0.00, 1.00, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.activation_parameters.act_next);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_act_next), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(0.00, 1.00, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.activation_parameters.act_prev);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_act_prev), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(-1.0, 0.00, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.activation_parameters.act_inhi);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_act_inhi), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    tmp = gtk_spin_button_new_with_range(0.01, 1.00, 0.01);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(tmp), globals->params.activation_parameters.persistence);
    g_signal_connect(G_OBJECT(tmp), "value_changed", G_CALLBACK(x_spin_persistence), globals);
    gtk_box_pack_start(GTK_BOX(vbox), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    */
    /* The control panel: */


      /* long hbox with two radio button frames in it */
    hbox_container = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page), hbox_container, FALSE, FALSE, 5);
    gtk_widget_show(hbox_container);

    frame = gtk_frame_new (NULL); 
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
    gtk_box_pack_start (GTK_BOX (hbox_container), frame, TRUE, TRUE, 5);
    gtk_widget_show(frame);

    /* first sub-box - DV select display radio buttons */
    hbox = gtk_hbox_new(FALSE, 0);
    // put visible frame here?
    gtk_container_add(GTK_CONTAINER(frame), hbox);
    gtk_widget_show(hbox);

    tmp = gtk_label_new("View:");
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    gtk_widget_show(tmp);

    tmp = gtk_radio_button_new_with_label(radio_group, "Tablulated DVs");
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(radio_select_table), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tmp), (globals->canvas1_selection == CANVAS_TABLE));
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(tmp));
    gtk_widget_show(tmp);

    tmp = gtk_radio_button_new_with_label(radio_group, "Primary DV Graph");
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(radio_select_global_graph), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tmp), (globals->canvas1_selection == CANVAS_GLOBAL));
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(tmp));
    gtk_widget_show(tmp);

    tmp = gtk_radio_button_new_with_label(radio_group, "2nd Order DV Graph");
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(radio_select_2nd_order_graph), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tmp), (globals->canvas1_selection == CANVAS_SECOND_ORDER));
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(tmp));
    gtk_widget_show(tmp);




#if FALSE
    tmp = gtk_check_button_new_with_label("Dynamic display");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tmp), globals->dynamic_canvases);
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(x_toggle_dynamic_display), globals);
    gtk_box_pack_end(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    gtk_widget_show(tmp);

    tmp = gtk_check_button_new_with_label("Colour");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tmp), globals->colour);
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(x_toggle_colour), globals);
    gtk_box_pack_end(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    gtk_widget_show(tmp);
#endif

    // insert frame for 2nd sub box here
    frame = gtk_frame_new (NULL);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
    gtk_box_pack_start (GTK_BOX (hbox_container), frame, TRUE, TRUE, 5);
    gtk_widget_show(frame);


    /* 2nd sub-box - dataset select */
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER(frame), hbox);
    gtk_widget_show (hbox);



    tmp = gtk_label_new ("Dataset:");
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    gtk_widget_show(tmp);

    tmp = gtk_radio_button_new_with_label(radio_group_dataset_select, "J. 1998");
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(radio_select_dataset_jahanshahi_1998), globals);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(tmp), FALSE);  // set default dataset
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    radio_group_dataset_select = gtk_radio_button_get_group(GTK_RADIO_BUTTON(tmp));
    gtk_widget_show(tmp);

    tmp = gtk_radio_button_new_with_label(radio_group_dataset_select, "J. 2006");
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(radio_select_dataset_jahanshahi_2006), globals);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(tmp), FALSE);  // set default dataset
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    radio_group_dataset_select = gtk_radio_button_get_group(GTK_RADIO_BUTTON(tmp));
    gtk_widget_show(tmp);

    tmp = gtk_radio_button_new_with_label(radio_group_dataset_select, "T. 1998");
    // select current dataset
    g_signal_connect(G_OBJECT(tmp), "toggled", G_CALLBACK(radio_select_dataset_towse_1998), globals);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(tmp), TRUE); // default dataset  
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    radio_group_dataset_select = gtk_radio_button_get_group(GTK_RADIO_BUTTON(tmp));
    gtk_widget_show(tmp);
    

    /* include 'refresh' button */
    

    /* A separator for aesthetic reasons: */
    tmp = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(page), tmp, FALSE, FALSE, 0);
    gtk_widget_show(tmp);

    /* The output panel: */

    tmp = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(tmp), "expose_event", G_CALLBACK(analysis_canvas1_event_expose), globals);
    gtk_box_pack_end(GTK_BOX(page), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    globals->output_panel1 = tmp;

    gtk_widget_show(page);
    return(page);
}

/*----------------------------------------------------------------------------*/

static void radio_select_generation_period(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas2_selection = CANVAS_VARY_PERIOD;
        x_draw_canvas2(globals);
    }
}

static void radio_select_wm_threshold(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas2_selection = CANVAS_VARY_THRESHOLD;
        x_draw_canvas2(globals);
    }
}

static void radio_select_monitoring_efficiency(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas2_selection = CANVAS_VARY_MONITORING;
        x_draw_canvas2(globals);
    }
}

static void radio_select_wm_update_efficiency(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas2_selection = CANVAS_VARY_UPDATE;
        x_draw_canvas2(globals);
    }
}

static void radio_select_task_setting_temperature(GtkWidget *caller, XGlobals *globals)
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(caller))) {
        globals->canvas2_selection = CANVAS_VARY_TEMPERATURE;
        x_draw_canvas2(globals);
    }
}

static GtkWidget *notepage_parameter_studies_create(XGlobals *globals)
{
    GtkWidget *page, *button, *hbox, *tmp;
    GtkToolItem *tool_item;
    GtkTooltips *tooltips;
    GSList *radio_group = NULL;

    page = gtk_vbox_new(FALSE, 0);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(page), hbox, FALSE, FALSE, 0);
    gtk_widget_show(hbox);

    tmp = gtk_label_new("Parameter study:");
    gtk_box_pack_start(GTK_BOX(hbox), tmp, FALSE, FALSE, 5);
    gtk_widget_show(tmp);

    tooltips = gtk_tooltips_new();

    tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_GOTO_LAST); // Run study
    g_signal_connect(G_OBJECT(tool_item), "clicked", G_CALLBACK(x_task_run_parameter_study), globals);
    gtk_box_pack_end(GTK_BOX(hbox), GTK_WIDGET(tool_item), FALSE, FALSE, 5);
    gtk_tooltips_set_tip(tooltips, GTK_WIDGET(tool_item), "Run full parameter study (36 subjects at each value of the parameter)", NULL);
    gtk_widget_show(GTK_WIDGET(tool_item));

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(page), hbox, FALSE, FALSE, 5);
    gtk_widget_show(hbox);

    /* NS period radio button here */

    button = gtk_radio_button_new_with_label(radio_group, "Generation Period");
    g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(radio_select_generation_period), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), (globals->canvas2_selection == CANVAS_VARY_PERIOD));
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
    gtk_widget_show(button);

    button = gtk_radio_button_new_with_label(radio_group, "WM threshold");
    g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(radio_select_wm_threshold), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), (globals->canvas2_selection == CANVAS_VARY_THRESHOLD));
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
    gtk_widget_show(button);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(page), hbox, FALSE, FALSE, 5);
    gtk_widget_show(hbox);

    button = gtk_radio_button_new_with_label(radio_group, "Monitoring efficiency");
    g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(radio_select_monitoring_efficiency), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), (globals->canvas2_selection == CANVAS_VARY_MONITORING));
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
    gtk_widget_show(button);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(page), hbox, FALSE, FALSE, 5);
    gtk_widget_show(hbox);

    button = gtk_radio_button_new_with_label(radio_group, "WM update efficiency");
    g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(radio_select_wm_update_efficiency), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), (globals->canvas2_selection == CANVAS_VARY_UPDATE));
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
    gtk_widget_show(button);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(page), hbox, FALSE, FALSE, 5);
    gtk_widget_show(hbox);

    button = gtk_radio_button_new_with_label(radio_group, "Task Setting temperature");
    g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(radio_select_task_setting_temperature), globals);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), (globals->canvas2_selection == CANVAS_VARY_TEMPERATURE));
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 5);
    radio_group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
    gtk_widget_show(button);

    /* A separator for aesthetic reasons: */
    tmp = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(page), tmp, FALSE, FALSE, 0);
    gtk_widget_show(tmp);

    /* The output panel: */

    tmp = gtk_drawing_area_new();
    g_signal_connect(G_OBJECT(tmp), "expose_event", G_CALLBACK(analysis_canvas2_event_expose), globals);
    gtk_box_pack_end(GTK_BOX(page), tmp, TRUE, TRUE, 0);
    gtk_widget_show(tmp);

    globals->output_panel2 = tmp;

    gtk_widget_show(page);
    return(page);
}

/*----------------------------------------------------------------------------*/

Boolean rng_widgets_create(XGlobals *globals, OosVars *gv)
{
  // RngDataset *current_data_set = NULL; // perhaps set default here?

  
    globals->gv = gv;

    if ((globals->window = gtk_window_new(GTK_WINDOW_TOPLEVEL)) == NULL) {
        return(FALSE);
    }
    else {
        GtkWidget *page, *notes, *toolbar;
	GtkToolItem *tool_item;
	GtkTooltips *tooltips;
        int position = 0;

        gtk_window_set_default_size(GTK_WINDOW(globals->window), 800, 600);
        gtk_window_set_title(GTK_WINDOW(globals->window), "X RNG Simulation 3.3 [02/02/2014]");
        g_signal_connect(G_OBJECT(globals->window), "delete_event", G_CALLBACK(event_delete), globals);
        g_signal_connect(G_OBJECT(globals->window), "destroy", G_CALLBACK(callback_destroy), globals);

        page = gtk_vbox_new(FALSE, 0);
        gtk_container_add(GTK_CONTAINER(globals->window), page);
        gtk_widget_show(page);

        /* The toolbar: */

        toolbar = gtk_toolbar_new();
        gtk_box_pack_start(GTK_BOX(page), toolbar, FALSE, FALSE, 0);
        gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
        gtk_widget_show(toolbar);

        tooltips = gtk_tooltips_new();

        tool_item = gtk_separator_tool_item_new();
        gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(tool_item), FALSE);
        gtk_tool_item_set_expand(GTK_TOOL_ITEM(tool_item), TRUE);
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, position++);
        gtk_widget_show(GTK_WIDGET(tool_item));

        tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_PRINT); // Save a snapshot of the canvases
        g_signal_connect(G_OBJECT(tool_item), "clicked", G_CALLBACK(x_print_canvas), globals);
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, position++);
        gtk_tooltips_set_tip(tooltips, GTK_WIDGET(tool_item), "Save a snapshot of the current canvas to a PDF file", NULL);
        gtk_widget_show(GTK_WIDGET(tool_item));

        tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_REFRESH); // Redraw canvases
        g_signal_connect(G_OBJECT(tool_item), "clicked", G_CALLBACK(x_redraw_canvases), globals);
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, position++);
        gtk_tooltips_set_tip(tooltips, GTK_WIDGET(tool_item), "Refresh all canvases", NULL);
        gtk_widget_show(GTK_WIDGET(tool_item));

        tool_item = gtk_tool_button_new_from_stock(GTK_STOCK_CLOSE); // Close/exit
        g_signal_connect(G_OBJECT(tool_item), "clicked", G_CALLBACK(callback_destroy), globals);
        gtk_toolbar_insert(GTK_TOOLBAR(toolbar), tool_item, position++);
        gtk_tooltips_set_tip(tooltips, GTK_WIDGET(tool_item), "Close and exit the application", NULL);
        gtk_widget_show(GTK_WIDGET(tool_item));

        notes = gtk_notebook_new();
        gtk_box_pack_start(GTK_BOX(page), notes, TRUE, TRUE, 0);
        globals->notebook = notes;
        gtk_widget_show(notes);

        gtk_notebook_append_page(GTK_NOTEBOOK(notes), diagram_create_notepage(globals), gtk_label_new("Architecture"));
        gtk_notebook_append_page(GTK_NOTEBOOK(notes), browser_create_notepage(globals), gtk_label_new("OOS Browser"));
        gtk_notebook_append_page(GTK_NOTEBOOK(notes), notepage_basic_results_create(globals), gtk_label_new("Basic Results"));
        gtk_notebook_append_page(GTK_NOTEBOOK(notes), notepage_parameter_studies_create(globals), gtk_label_new("Parameter Studies"));

        return(TRUE);
    }
}

/******************************************************************************/
