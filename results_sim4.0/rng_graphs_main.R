# main graphs for dissertation

rm (list = ls())
library(ggplot2) # for graphs

# import data


# -------------------- TARGET DATA graphs ---------------------------- #

data.zscores <- read.csv("RNG_targetdata_zscores.csv")
imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "MSc", "dissertation", "graphs", "target")



#--------------------- target data ----------------------

# R
graph.R <- ggplot (data.zscores, aes(x=interval, y=R.mean, colour=Dataset))
graph.R +
    ggtitle ("R score vs. gen. rate: Human subjects") +
    labs (x = "Generation interval /s", y = "R /SDs from ideally random", colour = "Data set") +
    scale_colour_discrete (labels=c("Jahanshahi et. al., (2000)", "Jahanshahi et. al., (2006)", "Towse (1998)")) +
    ylim(-3, 4) +
    geom_point (size=3) +
    geom_line (size=1) +
    geom_errorbar (aes(x=interval, ymax=R.mean+R.sd, ymin=R.mean-R.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.85,.9)
           )

imageFile <- file.path(imageDirectory, "R.png") 
ggsave(imageFile)



# RNG
graph.RNG <- ggplot (data.zscores, aes(x=interval, y=RNG.mean, colour=Dataset))
graph.RNG +
    ggtitle ("RNG score vs. gen. rate: Human subjects") +
    labs (x = "Generation interval /s", y = "RNG /SDs from ideally random") +
    scale_colour_discrete (labels=c("Jahanshahi et. al., (2000)", "Jahanshahi et. al., (2006)", "Towse (1998)")) +
    ylim(-3, 4) +
    geom_point (size=3) +
    geom_line (size=1) +
    geom_errorbar (aes(x=interval, ymax=RNG.mean+RNG.sd, ymin=RNG.mean-RNG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(0.15,0.15)
           )
imageFile <- file.path(imageDirectory, "RNG.png") 
ggsave(imageFile)

# CS1
graph.CS1 <- ggplot (data.zscores, aes(x=interval, y=CS1.mean, colour=Dataset))
graph.CS1 +
    ggtitle ("CS1 score vs. gen. rate: Human subjects") +
    labs (x = "Generation interval /s", y = "CS1 /SDs from ideally random") +
    scale_colour_discrete (labels=c("Jahanshahi et. al., (2000)", "Jahanshahi et. al., (2006)", "Towse (1998)")) +
    ylim(-2, 4) +
    geom_point (size=3) +
    geom_line (size=1) +
    geom_errorbar (aes(x=interval, ymax=CS1.mean+CS1.sd, ymin=CS1.mean-CS1.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CS1.png") 
ggsave(imageFile)

# CS2
graph.CS2 <- ggplot (data.zscores, aes(x=interval, y=CS2.mean, colour=Dataset))
graph.CS2 +
    ggtitle ("CS2 score vs. gen. rate: Human subjects") +
    labs (x = "Generation interval /s", y = "CS2 /SDs from ideally random") +
    scale_colour_discrete (labels=c("Jahanshahi et. al., (2000)", "Jahanshahi et. al., (2006)", "Towse (1998)")) +
    ylim(-2, 2) +
    geom_point (size=3) +
    geom_line (size=1) +
    geom_errorbar (aes(x=interval, ymax=CS2.mean+CS2.sd, ymin=CS2.mean-CS2.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CS2.png") 
ggsave(imageFile)


# CST
graph.CST <- ggplot (data.zscores, aes(x=interval, y=CST.mean, colour=Dataset))
graph.CST +
    ggtitle ("CST score vs. gen. rate: Human subjects") +
    labs (x = "Generation interval /s", y = "CST /SDs from ideally random") +
    scale_colour_discrete (labels=c("Jahanshahi et. al., (2000)", "Jahanshahi et. al., (2006)", "Towse (1998)")) +
    ylim(-1.5, 2.8) +
    geom_point (size=3) +
    geom_line (size=1) +
    geom_errorbar (aes(x=interval, ymax=CST.mean+CST.sd, ymin=CST.mean-CST.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CST.png") 
ggsave(imageFile)

# RG
graph.RG <- ggplot (data.zscores, aes(x=interval, y=RG.mean, colour=Dataset))
graph.RG +
    ggtitle ("RG score vs. gen. rate: Human subjects") +
    labs (x = "Generation interval /s", y = "RG /SDs from ideally random") +
    scale_colour_discrete (labels=c("Jahanshahi et. al., (2000)", "Jahanshahi et. al., (2006)", "Towse (1998)")) +
    ylim(0, 5.5) +
    geom_point (size=3) +
    geom_line (size=1) +
    geom_errorbar (aes(x=interval, ymax=RG.mean+RG.sd, ymin=RG.mean-RG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "RG.png") 
ggsave(imageFile)



# -------------------- SIMULATION 4 ------------------------------

data.zscores <- read.csv("RNG_simulation4_zscores.csv")
                 # use 'data - simulation3.ods' to create data file from output of simulation3.sh
imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "writing", "RNG paper", "graphs", "simulation4")

# R
graph.R <- ggplot (data.zscores, aes(x=interval, y=R.mean, colour=Dataset))
graph.R +
    ggtitle ("R score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "R /SDs from ideally random") +
    ylim(-2, 5) +
    geom_point (colour = "black", size=3) +
    geom_line (colour = "black", linetype = "dotted", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=R.mean+R.sd, ymin=R.mean-R.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "R.png") 
ggsave(imageFile)



# RNG
graph.RNG <- ggplot (data.zscores, aes(x=interval, y=RNG.mean, colour=Dataset))
graph.RNG +
    ggtitle ("RNG score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "RNG /SDs from ideally random") +
    ylim(-0, 7) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=RNG.mean+RNG.sd, ymin=RNG.mean-RNG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "RNG.png") 
ggsave(imageFile)

# CS1
graph.CS1 <- ggplot (data.zscores, aes(x=interval, y=CS1.mean, colour=Dataset))
graph.CS1 +
    ggtitle ("CS1 score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "CS1 /SDs from ideally random") +
    ylim(-2, 10) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS1.mean+CS1.sd, ymin=CS1.mean-CS1.sd, width=.1)) +
    geom_hline(yintercept=0) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CS1.png") 
ggsave(imageFile)

# CS2
graph.CS2 <- ggplot (data.zscores, aes(x=interval, y=CS2.mean, colour=Dataset))
graph.CS2 +
    ggtitle ("CS2 score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "CS2 /SDs from ideally random") +
    ylim(-2, 5) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS2.mean+CS2.sd, ymin=CS2.mean-CS2.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "CS2.png") 
ggsave(imageFile)


# CST
graph.CST <- ggplot (data.zscores, aes(x=interval, y=CST.mean, colour=Dataset))
graph.CST +
    ggtitle ("CST vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "CST /SDs from ideally random") +
    ylim(-1.5, 10) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_hline(yintercept=0) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CST.mean+CST.sd, ymin=CST.mean-CST.sd, width=.1)) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CST.png") 
ggsave(imageFile)

# RG
graph.RG <- ggplot (data.zscores, aes(x=interval, y=RG.mean, colour=Dataset))
graph.RG +
    ggtitle ("RG score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "RG /SDs from ideally random") +
    ylim(-2, 6.5) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=RG.mean+RG.sd, ymin=RG.mean-RG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "RG.png") 
ggsave(imageFile)





# -------------------- SIMULATION 3 ------------------------------

data.zscores <- read.csv("RNG_simulation3_zscores.csv")
                 # use 'data - simulation3.ods' to create data file from output of simulation3.sh
imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "writing", "RNG paper", "graphs")

# R
graph.R <- ggplot (data.zscores, aes(x=interval, y=R.mean, colour=Dataset))
graph.R +
    ggtitle ("R score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "R /SDs from ideally random") +
    ylim(-3, 4) +
    geom_point (colour = "black", size=3) +
    geom_line (colour = "black", linetype = "dotted", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=R.mean+R.sd, ymin=R.mean-R.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "R.png") 
ggsave(imageFile)



# RNG
graph.RNG <- ggplot (data.zscores, aes(x=interval, y=RNG.mean, colour=Dataset))
graph.RNG +
    ggtitle ("RNG score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "RNG /SDs from ideally random") +
    ylim(-1, 6) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=RNG.mean+RNG.sd, ymin=RNG.mean-RNG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "RNG.png") 
ggsave(imageFile)

# CS1
graph.CS1 <- ggplot (data.zscores, aes(x=interval, y=CS1.mean, colour=Dataset))
graph.CS1 +
    ggtitle ("CS1 score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "CS1 /SDs from ideally random") +
    ylim(-2, 4) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS1.mean+CS1.sd, ymin=CS1.mean-CS1.sd, width=.1)) +
    geom_hline(yintercept=0) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CS1.png") 
ggsave(imageFile)

# CS2
graph.CS2 <- ggplot (data.zscores, aes(x=interval, y=CS2.mean, colour=Dataset))
graph.CS2 +
    ggtitle ("CS2 score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "CS2 /SDs from ideally random") +
    ylim(-2, 2) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS2.mean+CS2.sd, ymin=CS2.mean-CS2.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "CS2.png") 
ggsave(imageFile)


# CST
graph.CST <- ggplot (data.zscores, aes(x=interval, y=CST.mean, colour=Dataset))
graph.CST +
    ggtitle ("CST vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "CST /SDs from ideally random") +
    ylim(-1.5, 2.8) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_hline(yintercept=0) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CST.mean+CST.sd, ymin=CST.mean-CST.sd, width=.1)) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CST.png") 
ggsave(imageFile)

# RG
graph.RG <- ggplot (data.zscores, aes(x=interval, y=RG.mean, colour=Dataset))
graph.RG +
    ggtitle ("RG score vs. gen. rate: Simulation 3") +
    labs (x = "Generation interval /cycles", y = "RG /SDs from ideally random") +
    ylim(0, 5.5) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=RG.mean+RG.sd, ymin=RG.mean-RG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "RG.png") 
ggsave(imageFile)




# -------------------- SIMULATION 2 ------------------------------

data.zscores <- read.csv("RNG_simulation2_zscores.csv")
imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "MSc", "dissertation", "graphs", "sim2")


#--------------------- Execute graphs  ----------------------

# R
graph.R <- ggplot (data.zscores, aes(x=interval, y=R.mean, colour=Dataset))
graph.R +
    ggtitle ("R score vs. gen. rate: Simulation 2") +
    labs (x = "Generation interval /cycles", y = "R /SDs from ideally random") +
    ylim(-3, 4) +
    geom_point (colour = "black", size=3) +
    geom_line (colour = "black", linetype = "dotted", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=R.mean+R.sd, ymin=R.mean-R.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "R.png") 
ggsave(imageFile)



# RNG
graph.RNG <- ggplot (data.zscores, aes(x=interval, y=RNG.mean, colour=Dataset))
graph.RNG +
    ggtitle ("RNG score vs. gen. rate: Simulation 2") +
    labs (x = "Generation interval /cycles", y = "RNG /SDs from ideally random") +
    ylim(-3, 4) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=RNG.mean+RNG.sd, ymin=RNG.mean-RNG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "RNG.png") 
ggsave(imageFile)

# CS1
graph.CS1 <- ggplot (data.zscores, aes(x=interval, y=CS1.mean, colour=Dataset))
graph.CS1 +
    ggtitle ("CS1 score vs. gen. rate: Simulation 2") +
    labs (x = "Generation interval /cycles", y = "CS1 /SDs from ideally random") +
    ylim(-2, 4) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS1.mean+CS1.sd, ymin=CS1.mean-CS1.sd, width=.1)) +
    geom_hline(yintercept=0) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CS1.png") 
ggsave(imageFile)

# CS2
graph.CS2 <- ggplot (data.zscores, aes(x=interval, y=CS2.mean, colour=Dataset))
graph.CS2 +
    ggtitle ("CS2 score vs. gen. rate: Simulation 2") +
    labs (x = "Generation interval /cycles", y = "CS2 /SDs from ideally random") +
    ylim(-2, 2) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS2.mean+CS2.sd, ymin=CS2.mean-CS2.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "CS2.png") 
ggsave(imageFile)


# CST
graph.CST <- ggplot (data.zscores, aes(x=interval, y=CST.mean, colour=Dataset))
graph.CST +
    ggtitle ("CST vs. gen. rate: Simulation 2") +
    labs (x = "Generation interval /cycles", y = "CST /SDs from ideally random") +
    ylim(-1.5, 2.8) +
    geom_point (size=3, colour = "black") +
    geom_line (linetype = "dotted", size=1, colour = "black") +
    geom_hline(yintercept=0) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CST.mean+CST.sd, ymin=CST.mean-CST.sd, width=.1)) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CST.png") 
ggsave(imageFile)

# RG
graph.RG <- ggplot (data.zscores, aes(x=interval, y=RG.mean, colour=Dataset))
graph.RG +
    ggtitle ("RG score vs. gen. rate: Simulation 2") +
    labs (x = "Generation interval /cycles", y = "RG /SDs from ideally random") +
    ylim(0, 5.5) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=RG.mean+RG.sd, ymin=RG.mean-RG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
       )
imageFile <- file.path(imageDirectory, "RG.png") 
ggsave(imageFile)



# ------------------------------- SIMULATION 1 --------------------------------

data.zscores <- read.csv("RNG_simulation1_zscores.csv")
imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "MSc", "dissertation", "graphs", "sim1")


#--------------------- Execute graphs  ----------------------

# R
graph.R <- ggplot (data.zscores, aes(x=interval, y=R.mean, colour=Dataset))
graph.R +
    ggtitle ("R score vs. gen. rate: Simulation 1") +
    labs (x = "Generation interval /cycles", y = "R /SDs from ideally random") +
    ylim(-3, 4) +
    geom_point (colour = "black", size=3) +
    geom_line (colour = "black", linetype = "dotted", size=1) +
    geom_hline(yintercept=0) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=R.mean+R.sd, ymin=R.mean-R.sd, width=.1)) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
              )
imageFile <- file.path(imageDirectory, "R.png") 
ggsave(imageFile)


# RNG
graph.RNG <- ggplot (data.zscores, aes(x=interval, y=RNG.mean, colour=Dataset))
graph.RNG +
    ggtitle ("RNG score vs. gen. rate: Simulation 1") +
    labs (x = "Generation interval /cycles", y = "RNG /SDs from ideally random") +
    ylim(-3, 4) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", colour = "black", aes(x=interval, ymax=RNG.mean+RNG.sd, ymin=RNG.mean-RNG.sd, width=.1)) +
    geom_hline(yintercept=0) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "RNG.png") 
ggsave(imageFile)

# CS1
graph.CS1 <- ggplot (data.zscores, aes(x=interval, y=CS1.mean, colour=Dataset))
graph.CS1 +
    ggtitle ("CS1 vs. gen. rate: Simulation 1") +
    labs (x = "Generation interval /cycles", y = "CS1 /SDs from ideally random") +
    ylim(-2, 4) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS1.mean+CS1.sd, ymin=CS1.mean-CS1.sd, width=.1)) +
    geom_hline(yintercept=0) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CS1.png") 
ggsave(imageFile)

# CS2
graph.CS2 <- ggplot (data.zscores, aes(x=interval, y=CS2.mean, colour=Dataset))
graph.CS2 +
    ggtitle ("CS2 vs. gen. rate: Simulation 1") +
    labs (x = "Generation interval /cycles", y = "CS2 /SDs from ideally random") +
    ylim(-2, 2) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CS2.mean+CS2.sd, ymin=CS2.mean-CS2.sd, width=.1)) +
    geom_hline(yintercept=0) +
        theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CS2.png") 
ggsave(imageFile)


# CST
graph.CST <- ggplot (data.zscores, aes(x=interval, y=CST.mean, colour=Dataset))
graph.CST +
    ggtitle ("CST vs. gen. rate: Simulation 1") +
    labs (x = "Generation interval /cycles", y = "CST /SDs from ideally random") +
    ylim(-1.5, 2.8) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=CST.mean+CST.sd, ymin=CST.mean-CST.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "CST.png") 
ggsave(imageFile)

# RG
graph.RG <- ggplot (data.zscores, aes(x=interval, y=RG.mean, colour=Dataset))
graph.RG +
    ggtitle ("RG score vs. gen. rate: Simulation 1") +
    labs (x = "Generation interval /cycles", y = "RG /SDs from ideally random") +
    ylim(0, 5.5) +
    geom_point (colour = "black", size=3) +
    geom_line (linetype = "dotted", colour = "black", size=1) +
    geom_errorbar (colour = "black", aes(x=interval, ymax=RG.mean+RG.sd, ymin=RG.mean-RG.sd, width=.1)) +
    geom_hline(yintercept=0) +
    theme ( axis.text.x = element_text(family="Arial", size=rel(2)),
            axis.text.y = element_text(family="Arial", size=rel(2)),
            axis.title.x = element_text(family="Arial", size=rel(2)),
            axis.title.y = element_text(family="Arial", size=rel(2)),
            plot.title = element_text(family="Arial", size=rel(2)),
            legend.position = c(.9,.9)
           )
imageFile <- file.path(imageDirectory, "RG.png") 
ggsave(imageFile)
