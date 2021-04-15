# CPP Projet Modelisation
# file name : plotMvAvg.r
# authors : Belmahi Asmae, Maxwell Sam
# date : 14/04/2021	
dev.new("AVGplot.pdf",width=7, height=4)
df1=read.table("channel_2.txt",header=T)
df2=read.table("mvAvg_channel_2.txt", header=T)
plot(df1[,1],df1[,2], main = "Evolution of action potential on the first 8 seconds\nand its baseline",
	type="l", 
	col="#3182bd", 
	xlab = "time [s.10E-3]", 
	ylab = "Signal [mv]"
	)
lines(df2[,1], df2[,2], col="red") # temps en ms
legend("bottomright", c("signal", "baseline"), col=c("#3182bd", "red"), lty=1, cex=1)
