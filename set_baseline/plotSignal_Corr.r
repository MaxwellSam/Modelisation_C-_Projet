# CPP Projet Modelisation
# file name : plotSignal.r
# authors : Belmahi Asmae, Maxwell Sam
# date : 14/04/2021	
dev.new(width=7, height=8)
par(mfrow=c(2,1))
df1=read.table("channel_2.txt",header=T)
df2=read.table("corr_channel_2.txt",header=T)
plot(df1[,1], df1[,2], main = "Signal befor correction with baseline",
	type="l", 
	col="#3182bd", 
	xlab = "time [ms]", 
	ylab = "Signal [mv]"
	) 
plot(df2[,1], df2[,2], main = "Signal after correction with baseline",
	type="l", 
	col="#3182bd", 
	xlab = "time [ms]", 
	ylab = "Signal [mv]"
	) 
