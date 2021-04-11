df=read.table("channel_3.txt",header=T)
plot(df[,1],df[,2],type="l", xlab = "channel_3 [mv]", ylab = "time") # temps en ms