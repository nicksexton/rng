/*******************************************************************************

    File:     rng_client.c
    Author:   Rick Cooper
    Created:  08/07/12
    Edited:   08/07/12
    Contents: LibExpress interface to the RNG model

    Public procedures:
        int main(int argc, char **argv)

*******************************************************************************/

#include "rng.h"
#include <libexpress.h>

#define SERVER_PAGE "/rcooper/experiments/rng_s5/express.cgi"

/******************************************************************************/
/* Section 1: Main -----------------------------------------------------------*/

int main(int argc, char **argv)
{
    OosVars *gv;
    RngParameters pars = {10.0, 1.0, 1.0, 40};
    double fit_max;
    int trial, block, pid;

    if ((gv = oos_globals_create()) == NULL) {
        fprintf(stdout, "ABORTING: Cannot allocate global variable space\n");
    }
    else {
        server_set(SP_HOST, "sideshow.psyc.bbk.ac.uk");
        server_set(SP_PAGE, SERVER_PAGE);

        server_declare_variable("trial", VAR_WIV, VAR_INT, &trial);
        server_declare_variable("block", VAR_WIV, VAR_INT, &block);

        server_declare_variable("temperature", VAR_BIV, VAR_DOUBLE, &(pars.temperature));
        server_declare_variable("monitoring_efficiency", VAR_BIV, VAR_DOUBLE, &(pars.monitoring_efficiency));
        server_declare_variable("wm_update_rate", VAR_BIV, VAR_DOUBLE, &(pars.wm_update_rate));
        server_declare_variable("wm_decay_rate", VAR_BIV, VAR_INT, &(pars.wm_decay_rate));

        server_declare_variable("rng_fit_max", VAR_DV, VAR_DOUBLE, &fit_max);

        while ((pid = server_next_participant()) > 0) {
            do {
                RngData *task_data;

                rng_create(gv, &pars);
                rng_initialise_model(gv);
                rng_run(gv);
                rng_analyse_group_data(gv, NULL);
                task_data = (RngData *)gv->task_data;
                fit_max = rng_global_fit_max(&(task_data->group_means), &subject_ctl_means);
                rng_globals_destroy((RngData *)gv->task_data);
                gv->task_data = NULL;
            } while (server_next_hit(pid) > 0);
        }
    }
    oos_globals_destroy(gv);
    server_free();

    exit(0);
}

/******************************************************************************/
