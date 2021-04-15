# CPP Projet Modelisation
# file name : plotSignal.r
# authors : Belmahi Asmae, Maxwell Sam
# date : 14/04/2021	
dev.new(width=7, height=4)
df=read.table("channel_2.txt",header=T)
plot(df[,1], df[,2], main = "Evolution of action potential on the first 8 seconds",
	type="l", 
	col="#3182bd", 
	xlab = "time [ms]", 
	ylab = "Signal [mv]"
	) 
