# R data analysis for simulation 3

rm (list = ls())

library(compute.es) # for effect sizes
library(car) # for Levene's test
library(ggplot2) # for graphs
library(multcomp) # for post-hoc tests
library(pastecs) # for descriptive statistics

library (lsr) # for eta squared

#build the data matrixg
enerationPeriod<-gl(6, 36, labels = c(40, 34, 29, 23, 18, 12))
generationInterval<-gl(6, 36, labels = c("3.0", "2.5", "2.0", "1.5", "1.0", "0.5"))
simulation<-cbind(generationPeriod, generationInterval, read.delim("simulation3_data.txt", header = TRUE))
# simulation3_data contains data per simulated subject, created by simulation3.sh
simulation.imageDirectory <- file.path(Sys.getenv("HOME"), "Dropbox", "writing", "RNG paper", "graphs")



#----------------------------------------------- R ------------------------------------------------
                                        # plot graphs of means & error bars
line <- ggplot (simulation, aes(generationPeriod, R))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "R")
imageFile <- file.path(simulation.imageDirectory, "simulation3 means R.png") 
ggsave(imageFile)

                                        # a histogram, qq plot and boxplots to visually check data
R.histogram <- ggplot (simulation, aes(R)) + theme(legend.position = "none") 
R.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "R score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$R, na.rm = TRUE), sd = sd(simulation$R, na.rm = TRUE)), colour = "blue", size = 1)

R.qqplot <- qplot(sample = simulation$R, stat = "qq")
R.qqplot

R.boxplot <- ggplot(simulation, aes(generationPeriod, R))
R.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "R")


                                        # descriptives
by(simulation$R, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
# note: some conditions affected by positive skew, however sample size big enough to assume
# sampling dist. is normal

                                        # Levene's test
leveneTest(simulation$R, simulation$generationPeriod, center = median)
# levene's test ns.

                                        # main analysis
simulation.model.R <- aov(R ~ generationPeriod, data = simulation)
summary (simulation.model.R)
# n.s. main effect of gen rate on R


#----------------------------------------------- RNG ------------------------------------------------
line <- ggplot (simulation, aes(generationPeriod, RNG))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "RNG")
imageFile <- file.path(simulation.imageDirectory, "simulation3 means RNG.png") 
ggsave(imageFile)

                                        # a histogram and a qq plot to visually check normality
RNG.histogram <- ggplot (simulation, aes(RNG)) + theme(legend.position = "none")
RNG.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "RNG score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$RNG, na.rm = TRUE), sd = sd(simulation$RNG, na.rm = TRUE)), colour = "blue", size = 1)


RNG.qqplot <- qplot(sample = simulation$RNG, stat = "qq")
RNG.qqplot



RNG.boxplot <- ggplot(simulation, aes(generationPeriod, RNG))
RNG.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "RNG")


                                        # descriptives
by(simulation$RNG, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)

                                        # Levene's test
leveneTest(simulation$RNG, simulation$generationPeriod, center = median)
# Levene's test significant, p = .023
# however ratio of variances for raw data (Hartley's Fmax) = 2.47 - considered robust for ANOVA




                                        # main analysis
simulation.model.RNG <- aov(RNG ~ generationPeriod, data = simulation)
summary (simulation.model.RNG)
# sig. main effect of gen rate on RNG F(5,210) = 2.60, p = 0.026


                                        #effect sizes
#simulation.model.RNG.r <- summary.lm(simulation.model.RNG)
#simulation.model.RNG.r$"r.squared"
#sqrt(simulation.model.RNG.r$"r.squared") #r

etaSquared (simulation.model.RNG, type = 2, anova = FALSE)


#----------------------------------------------- CS1 ------------------------------------------------
line <- ggplot (simulation, aes(generationPeriod, CS1))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "CS1")
imageFile <- file.path(simulation.imageDirectory, "simulation3 means CS1.png") 
ggsave(imageFile)


                                        # a histogram and a qq plot to visually check normality
CS1.histogram <- ggplot (simulation, aes(CS1)) + theme(legend.position = "none") 
CS1.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "CS1 score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$CS1, na.rm = TRUE), sd = sd(simulation$CS1, na.rm = TRUE)), colour = "blue", size = 1)


CS1.qqplot <- qplot(sample = simulation$CS1, stat = "qq")
CS1.qqplot


CS1.boxplot <- ggplot(simulation, aes(generationPeriod, CS1))
CS1.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "CS1")


                                        # descriptives
by(simulation$CS1, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
                                        # Levene's test
leveneTest(simulation$CS1, simulation$generationPeriod, center = median)
                                        #positive skew, levene's test highly significant

#sqrt transformation
simulation$sqrt.CS1 <- sqrt(simulation$CS1)

sqrt.CS1.histogram <- ggplot (simulation, aes(sqrt.CS1)) + theme(legend.position = "none") 
sqrt.CS1.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "sqrt CS1 score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$sqrt.CS1, na.rm = TRUE), sd = sd(simulation$sqrt.CS1, na.rm = TRUE)), colour = "blue", size = 1)

sqrt.CS1.boxplot <- ggplot(simulation, aes(generationPeriod, sqrt.CS1))
sqrt.CS1.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "sqrt CS1")


by(simulation$sqrt.CS1, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
leveneTest(simulation$sqrt.CS1, simulation$generationPeriod, center = median)
#skew improved, levene's test still signf. but variances less than the 4x suggested by howell


#log transformation
simulation$log.CS1 <- log(simulation$CS1)

log.CS1.histogram <- ggplot (simulation, aes(log.CS1)) + theme(legend.position = "none") 
log.CS1.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "log CS1 score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$log.CS1, na.rm = TRUE), sd = sd(simulation$log.CS1, na.rm = TRUE)), colour = "blue", size = 1)

log.CS1.boxplot <- ggplot(simulation, aes(generationPeriod, log.CS1))
log.CS1.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "log CS1")


by(simulation$log.CS1, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
leveneTest(simulation$log.CS1, simulation$generationPeriod, center = median)
#skew ok, levene's still v signf
# Hartley's Fmax = 5.138




                                        # main analysis
# NOTE Welch's F test as Levene's test is highly significant
oneway.test(CS1 ~ generationPeriod, data = simulation)

                                        #effect sizes
simulation.model.CS1 <- aov(CS1 ~ generationPeriod, data = simulation)
etaSquared (simulation.model.CS1, type = 2, anova = FALSE)






#----------------------------------------------- CS2 ------------------------------------------------
line <- ggplot (simulation, aes(generationPeriod, CS2))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "CS2")
imageFile <- file.path(simulation.imageDirectory, "simulation3 means CS2.png") 
ggsave(imageFile)

                                        # a histogram and a qq plot to visually check normality
CS2.histogram <- ggplot (simulation, aes(CS2)) + theme(legend.position = "none") 
CS2.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "CS2 score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$CS2, na.rm = TRUE), sd = sd(simulation$CS2, na.rm = TRUE)), colour = "blue", size = 1)

CS2.qqplot <- qplot(sample = simulation$CS1, stat = "qq")
CS2.qqplot


CS2.boxplot <- ggplot(simulation, aes(generationPeriod, CS2))
CS2.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "CS2")




                                        # descriptives
by(simulation$CS2, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)

                                        # Levene's test
leveneTest(simulation$CS2, simulation$generationPeriod, center = median)

#underlying distribution skew but probably ok, levene's test ns.

                                        # main analysis
simulation.model.CS2 <- aov(CS2 ~ generationPeriod, data = simulation)
summary (simulation.model.CS2)

                                        # effect sizes
simulation.model.CS1 <- aov(CS2 ~ generationPeriod, data = simulation)
etaSquared (simulation.model.CS2, type = 2, anova = FALSE)



# log transform so effect sizes etc. are directly comparable with CS1

#simulation$log.CS2 <- log(simulation$CS2)
#
#log.CS2.histogram <- ggplot (simulation, aes(log.CS2)) + theme(legend.position = "none") 
#log.CS2.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "log CS2 score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$log.CS2, na.rm = TRUE), sd = sd(simulation$log.CS2, na.rm = TRUE)), colour = "blue", size = 1)

#log.CS2.boxplot <- ggplot(simulation, aes(generationPeriod, log.CS2))
#log.CS2.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "log CS2")


#by(simulation$log.CS2, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
#leveneTest(simulation$log.CS2, simulation$generationPeriod, center = median)



# anova on log transformed data
#simulation.model.log.CS2 <- aov(log.CS2 ~ generationPeriod, data = simulation)
#summary (simulation.model.log.CS2)

                                        # effect sizes
#simulation.model.log.CS2.r <- summary.lm(simulation.model.log.CS2)
#simulation.model.log.CS2.r$"r.squared"
#sqrt(simulation.model.log.CS2.r$"r.squared") #r



#----------------------------------------------- CST ------------------------------------------------
line <- ggplot (simulation, aes(generationPeriod, CST))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "CST")
imageFile <- file.path(simulation.imageDirectory, "simulation3 means CST.png") 
ggsave(imageFile)

                                        # a histogram and a qq plot to visually check normality
CST.histogram <- ggplot (simulation, aes(CST)) + theme(legend.position = "none") 
CST.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "CST score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$CST, na.rm = TRUE), sd = sd(simulation$CST, na.rm = TRUE)), colour = "blue", size = 1)

CST.qqplot <- qplot(sample = simulation$CST, stat = "qq")
CST.qqplot


CST.boxplot <- ggplot(simulation, aes(generationPeriod, CST))
CST.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "CST")


# some skew but acceptable, levene's test highly sig. 

                                        # descriptives
by(simulation$CST, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)

                                        # Levene's test
leveneTest(simulation$CST, simulation$generationPeriod, center = median)

                                        # main analysis
# Welch's F test as Levene's test is highly significant
# also don't transform data so effect sizes are consistent with CS1, CS2
oneway.test(CST ~ generationPeriod, data = simulation)





                                        # effect sizes
simulation.model.CST <- aov(CST ~ generationPeriod, data = simulation)
etaSquared (simulation.model.CST, type = 2, anova = FALSE)



#----------------------------------------------- RG ------------------------------------------------
line <- ggplot (simulation, aes(generationPeriod, RG))
line + stat_summary(fun.y = mean, geom = "point") + stat_summary(fun.y = mean, geom = "line", aes(group=1), colour="Blue", linetype="dashed") + stat_summary(fun.data = mean_cl_boot, geom = "errorbar", width = 0.2) + labs(x = "Generation Period", y = "RG")
imageFile <- file.path(simulation.imageDirectory, "simulation3  means RG.png") 
ggsave(imageFile)

                                        # a histogram and some other plots to inspect data
RG.histogram <- ggplot (simulation, aes(RG)) + theme(legend.position = "none") 
RG.histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "RG score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$RG, na.rm = TRUE), sd = sd(simulation$RG, na.rm = TRUE)), colour = "blue", size = 1)

RG.qqplot <- qplot(sample = simulation$RG, stat = "qq")
RG.qqplot

RG.boxplot <- ggplot(simulation, aes(generationPeriod, RG))
RG.boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "RG")



                                        # descriptives
by(simulation$RG, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)

                                        # Levene's test
leveneTest(simulation$RG, simulation$generationPeriod, center = median)

                                        # main analysis
simulation.model.RG <- aov(RG ~ generationPeriod, data = simulation)
summary (simulation.model.RG)


                                        # effect sizes
simulation.model.RG <- aov(RG ~ generationPeriod, data = simulation)
etaSquared (simulation.model.RG, type = 2, anova = FALSE)


