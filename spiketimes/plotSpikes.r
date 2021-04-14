# CPP Projet Modelisation
# file name : plotSpikes.r
# authors : Belmahi Asmae, Maxwell Sam
# date : 14/04/2021	

dev.new(width=7, height=4)
df=read.table("spikes_channel_2.txt",header=T)
plot(df[,1], df[,2], main = "Identification of spikes on the record channel",
	type="l", 
	col="#3182bd", 
	xlab = "time [ms]", 
	ylab = "Signal [mv]"
	)

lines(df[,1], df[,4], col="black")
points(df[,1], df[,3], col="red")


