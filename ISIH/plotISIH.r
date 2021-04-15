# CPP Projet Modelisation
# file name : plotSpikes.r
# authors : Belmahi Asmae, Maxwell Sam
# date : 14/04/2021	

dev.new(width=7, height=4)
df=read.table("isih_2.txt",header=F)

hist(df[,1], 
	main = "ISIH\nDistribution of time between two spikes", 
	xlab = "delta time [ms]", 
	col = "#3182bd", 
	breaks=40
	)

