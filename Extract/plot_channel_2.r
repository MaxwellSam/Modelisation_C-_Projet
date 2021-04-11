df=read.table("channel_2.txt",header=T)
plot(df[,1],df[,2],type="l", xlab = "channel_2 [mv]", ylab = "time") # temps en ms