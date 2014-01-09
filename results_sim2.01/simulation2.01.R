# R data analysis for simulation 1.2
# one-way ANOVA for indices of randomness, six conditions


library(compute.es) # for effect sizes
library(car) # for Levene's test
library(ggplot2) # for graphs
library(multcomp) # for post-hoc tests
library(pastecs) # for descriptive statistics

#build the data matrix
generationPeriod<-gl(6, 36, labels = c(40, 34, 29, 23, 18, 12))
generationInterval<-gl(6, 36, labels = c("3.0", "2.5", "2.0", "1.5", "1.0", "0.5"))
simulation2.01<-cbind(generationPeriod, generationInterval, read.delim("simulation2.01_data.txt", header = TRUE))

simulation2.01.imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "MSc", "dissertation", "graphs", "simulation2.01")


#----------------------------------------------- R ------------------------------------------------
                                        # plot graphs of means & error bars
line <- ggplot (simulation2.01, aes(generationPeriod, R))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "R")
imageFile <- file.path(simulation2.01.imageDirectory, "simulation2.01 means R.png") 
ggsave(imageFile)


                                        # descriptives
by(simulation2.01$R, simulation2.01$generationPeriod, stat.desc)

                                        # Levene's test
leveneTest(simulation2.01$R, simulation2.01$generationPeriod, center = median)

                                        # main ANOVA
simulation2.01.model.R <- aov(R ~ generationPeriod, data = simulation2.01)
summary (simulation2.01.model.R)

                                        #effect sizes
simulation2.01.model.R.r <- summary.lm(simulation2.01.model.R)
simulation2.01.model.R.r$"r.squared"


#----------------------------------------------- RNG ------------------------------------------------
line <- ggplot (simulation2.01, aes(generationPeriod, RNG))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "RNG")
imageFile <- file.path(simulation2.01.imageDirectory, "simulation2.01 means RNG.png") 
ggsave(imageFile)


                                        # descriptives
by(simulation2.01$RNG, simulation2.01$generationPeriod, stat.desc)

                                        # Levene's test
leveneTest(simulation2.01$RNG, simulation2.01$generationPeriod, center = median)

                                        # main ANOVA
simulation2.01.model.RNG <- aov(RNG ~ generationPeriod, data = simulation2.01)
summary (simulation2.01.model.RNG)

                                        #effect sizes
simulation2.01.model.RNG.r <- summary.lm(simulation2.01.model.RNG)
simulation2.01.model.RNG.r$"r.squared"



#----------------------------------------------- CS1 ------------------------------------------------
line <- ggplot (simulation2.01, aes(generationPeriod, CS1))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "CS1")
imageFile <- file.path(simulation2.01.imageDirectory, "simulation2.01 means CS1.png") 
ggsave(imageFile)


                                        # descriptives
by(simulation2.01$CS1, simulation2.01$generationPeriod, stat.desc)

                                        # Levene's test
leveneTest(simulation2.01$CS1, simulation2.01$generationPeriod, center = median)

                                        # main ANOVA
# NOTE Welch's F test as Levene's test is highly significant
oneway.test(CS1 ~ generationPeriod, data = simulation2.01)

                                        #effect sizes
simulation2.01.model.CS1 <- aov(CS1 ~ generationPeriod, data = simulation2.01)
simulation2.01.model.CS1.r <- summary.lm(simulation2.01.model.CS1)
simulation2.01.model.CS1.r$"r.squared"


#----------------------------------------------- CS2 ------------------------------------------------
line <- ggplot (simulation2.01, aes(generationPeriod, CS2))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "CS2")
imageFile <- file.path(simulation2.01.imageDirectory, "simulation2.01 means CS2.png") 
ggsave(imageFile)



                                        # descriptives
by(simulation2.01$CS2, simulation2.01$generationPeriod, stat.desc)

                                        # Levene's test
leveneTest(simulation2.01$CS2, simulation2.01$generationPeriod, center = median)

                                        # main ANOVA
# NOTE Welch's F test as Levene's test is highly significant
oneway.test(CS2 ~ generationPeriod, data = simulation2.01)


                                        #effect sizes
simulation2.01.model.CS2 <- aov(CS2 ~ generationPeriod, data = simulation2.01)
simulation2.01.model.CS2.r <- summary.lm(simulation2.01.model.CS2)
simulation2.01.model.CS2.r$"r.squared"

#----------------------------------------------- CST ------------------------------------------------
line <- ggplot (simulation2.01, aes(generationPeriod, CST))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "CST")
imageFile <- file.path(simulation2.01.imageDirectory, "simulation2.01 means CST.png") 
ggsave(imageFile)

                                        # descriptives
by(simulation2.01$CST, simulation2.01$generationPeriod, stat.desc)

                                        # Levene's test
leveneTest(simulation2.01$CST, simulation2.01$generationPeriod, center = median)

                                        # main ANOVA
# NOTE Welch's F test as Levene's test is highly significant
oneway.test(CST ~ generationPeriod, data = simulation2.01)


                                        #effect sizes
simulation2.01.model.CST <- aov(CST ~ generationPeriod, data = simulation2.01)
simulation2.01.model.CST.r <- summary.lm(simulation2.01.model.CST)
simulation2.01.model.CST.r$"r.squared"


#----------------------------------------------- RG ------------------------------------------------
line <- ggplot (simulation2.01, aes(generationPeriod, RG))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "RG")
imageFile <- file.path(simulation2.01.imageDirectory, "simulation2.01 means RG.png") 
ggsave(imageFile)



                                        # descriptives
by(simulation2.01$RG, simulation2.01$generationPeriod, stat.desc)

                                        # Levene's test
leveneTest(simulation2.01$RG, simulation2.01$generationPeriod, center = median)

                                        # main ANOVA
simulation2.01.model.RG <- aov(RG ~ generationPeriod, data = simulation2.01)
summary(simulation2.01.model.RG)

                                        #effect sizes
simulation2.01.model.RG.r <- summary.lm(simulation2.01.model.RG)
simulation2.01.model.RG.r$"r.squared"
