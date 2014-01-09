library (pastecs) # for stat.desc
library(psych) # for describe

generationPeriod<-gl(6, 36, labels = c(40, 33, 26, 18, 11, 4))
generationInterval<-gl(6, 36, labels = c("3.0", "2.5", "2.0", "1.5", "1.0", "0.5"))
simulation<-cbind(generationPeriod, generationInterval, read.delim("simulation1.2_data.txt", header = TRUE))

# ------------------------------- R stat -------------------------------

# a histogram and a qq plot to visually check normality
R_histogram <- ggplot (simulation, aes(R)) + theme(legend.position = "none") 
R_histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "R score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$R, na.rm = TRUE), sd = sd(simulation$R, na.rm = TRUE)), colour = "blue", size = 1)

qqplot.R <- qplot(sample = simulation$R, stat = "qq")
qqplot.R

R_boxplot <- ggplot(simulation, aes(generationPeriod, R))
R_boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "R")


# ------------------------------- RNG graphs ---------------------------

# a histogram and a qq plot to visually check normality
RNG_histogram <- ggplot (simulation, aes(RNG)) + theme(legend.position = "none")
RNG_histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "RNG score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$RNG, na.rm = TRUE), sd = sd(simulation$RNG, na.rm = TRUE)), colour = "blue", size = 1)


qqplot.RNG <- qplot(sample = simulation$RNG, stat = "qq")
qqplot.RNG



RNG_boxplot <- ggplot(simulation, aes(generationPeriod, RNG))
RNG_boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "RNG")


# ------------------------------ CS1 graphs -----------------------------

# a histogram and a qq plot to visually check normality
CS1_histogram <- ggplot (simulation, aes(CS1)) + theme(legend.position = "none") 
CS1_histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "CS1 score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$CS1, na.rm = TRUE), sd = sd(simulation$CS1, na.rm = TRUE)), colour = "blue", size = 1)


qqplot.CS1 <- qplot(sample = simulation$CS1, stat = "qq")
qqplot.CS1


CS1_boxplot <- ggplot(simulation, aes(generationPeriod, CS1))
CS1_boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "CS1")


# ------------------------------ CS2 graphs -----------------------------

# a histogram and a qq plot to visually check normality
CS2_histogram <- ggplot (simulation, aes(CS2)) + theme(legend.position = "none") 
CS2_histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "CS2 score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$CS2, na.rm = TRUE), sd = sd(simulation$CS2, na.rm = TRUE)), colour = "blue", size = 1)

qqplot.CS2 <- qplot(sample = simulation$CS1, stat = "qq")
qqplot.CS2


CS2_boxplot <- ggplot(simulation, aes(generationPeriod, CS2))
CS2_boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "CS2")


# ------------------------------ CST graphs ------------------------------

CST_histogram <- ggplot (simulation, aes(CST)) + theme(legend.position = "none") 
CST_histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "CST score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$CST, na.rm = TRUE), sd = sd(simulation$CST, na.rm = TRUE)), colour = "blue", size = 1)

qqplot.CST <- qplot(sample = simulation$CST, stat = "qq")
qqplot.CST


CST_boxplot <- ggplot(simulation, aes(generationPeriod, CST))
CST_boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "CST")



# ------------------------------ RG graphs ------------------------------

RG_histogram <- ggplot (simulation, aes(RG)) + theme(legend.position = "none") 
RG_histogram + geom_histogram(aes(y = ..density..), colour = "black", fill = "white") + labs (x = "RG score", y = "density") + stat_function(fun = dnorm, args = list(mean = mean(simulation$RG, na.rm = TRUE), sd = sd(simulation$RG, na.rm = TRUE)), colour = "blue", size = 1)

qqplot.RG <- qplot(sample = simulation$RG, stat = "qq")
qqplot.RG


RG_boxplot <- ggplot(simulation, aes(generationPeriod, RG))
RG_boxplot + geom_boxplot() + labs (x = "Generation Period (cycles)", y = "RG")



# overall descriptive stats
stat.desc( cbind( simulation$R, simulation$RNG, simulation$CS1, simulation$CS2, simulation$CST, simulation$RG), basic = FALSE, norm = TRUE)

# descriptive stats by condition
by(simulation$R, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
by(simulation$RNG, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
by(simulation$CS1, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
by(simulation$CS2, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
by(simulation$CST, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
by(simulation$RG, simulation$generationPeriod, stat.desc, basic = FALSE, norm = TRUE)
