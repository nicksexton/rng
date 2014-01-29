# main graphs for dissertation

rm (list = ls())
library(ggplot2) # for graphs

# import data

data <- read.csv("RNG_associates_data-sim4.csv", header=TRUE)
# names(data) <- c("dataset", "gen_interval", "associate", "mean_freq", "sd")

imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "writing", "RNG paper", "graphs", "simulation4")


#bargraph <- ggplot (data, aes(x = associate, y = mean_freq, colour = gen_interval, group = gen_interval))
#bargraph +
#    facet_wrap(~ dataset, nrow = 3, ncol = 1) +
#    geom_line ()

#----------------------- Towse graph -----------------------

data.graph = subset(data, dataset =="Towse 1998")


#----------------------- Simulation 1 -----------------------

data.graph = subset(data, dataset =="simulation1" & (gen_interval == 4 | gen_interval == 20 | gen_interval == 36))


linegraph <- ggplot (data.graph, width=16, height=12, aes(x = associate, y = mean_freq, colour = gen_interval, group = gen_interval))
linegraph +
    geom_line (size = 1.5) +
    geom_point (size = 2.5) +
    geom_errorbar (aes( ymin=mean_freq - sd, ymax = mean_freq + sd), position = "dodge", width = .2) +
    scale_x_continuous(breaks = seq(-9, 9, by=1)) +
    ggtitle ("Relative Associates Usage: Simulation 1") +
    labs (x = "Associate", y = "Relative frequency", colour = "Generation Interval (cycles)") +    
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.85)
           )
imageFile <- file.path(imageDirectory, "associates_11.png") 
ggsave(imageFile, width=16, height=12)



# --------------------- Simulation 2 ------------------------

data.graph = subset(data, dataset =="simulation2" & (gen_interval == 12 | gen_interval == 32 | gen_interval == 40))


linegraph <- ggplot (data.graph, width=16, height=12, aes(x = associate, y = mean_freq, colour = gen_interval, group = gen_interval))
linegraph +
    geom_line (size = 1.5) +
    geom_point (size = 2.5) +
    geom_errorbar (aes( ymin=mean_freq - sd, ymax = mean_freq + sd), position = "dodge", width = .2) +
    scale_x_continuous(breaks = seq(-9, 9, by=1)) +
    ggtitle ("Relative Associates Usage: Simulation 2") +
    labs (x = "Associate", y = "Relative frequency", colour = "Generation Interval (cycles)") +    
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.85)
           )
imageFile <- file.path(imageDirectory, "associates_2.png") 
ggsave(imageFile, width=16, height=12)




# --------------------- Simulation 3 ------------------------

data.graph = subset(data, dataset =="simulation3" & (gen_interval == 12 | gen_interval == 32 | gen_interval == 40))



linegraph <- ggplot (data.graph, width=16, height=12, aes(x = associate, y = mean_freq, colour = gen_interval, group = gen_interval))
linegraph +
    geom_line (size = 1.5) +
    geom_point (size = 2.5) +
    geom_errorbar (aes( ymin=mean_freq - sd, ymax = mean_freq + sd), position = "dodge", width = .2) +
    scale_x_continuous(breaks = seq(-9, 9, by=1)) +
    ggtitle ("Relative Associates Usage: Simulation 3") +
    labs (x = "Associate", y = "Relative frequency", colour = "Generation Interval (cycles)") +    
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.85)
           )
imageFile <- file.path(imageDirectory, "associates_3.png") 
ggsave(imageFile, width=16, height=12)




# --------------------- Simulation 4 ------------------------

data.graph = subset(data, dataset =="simulation4" & (gen_interval == 4 | gen_interval == 28 | gen_interval == 36 ))





linegraph <- ggplot (data.graph, width=16, height=12, aes(x = associate, y = mean_freq, colour = gen_interval, group = gen_interval))
linegraph +
    geom_line (size = 1.5) +
    geom_point (size = 2.5) +
    geom_errorbar (aes( ymin=mean_freq - sd, ymax = mean_freq + sd), position = "dodge", width = .2) +
    scale_x_continuous(breaks = seq(-9, 9, by=1)) +
    ggtitle ("Relative Associates Usage: Simulation 4") +
    labs (x = "Associate", y = "Relative frequency", colour = "Generation Interval (cycles)") +    
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.85)
           )
imageFile <- file.path(imageDirectory, "associates_4.png") 
ggsave(imageFile, width="16", height="12")

