# CPP Projet Modelisation
# file name : plotSpikes.r
# authors : Belmahi Asmae, Maxwell Sam
# date : 14/04/2021	

dev.new(width=7, height=4)
df=read.table("overlay_channel_2.txt",header=F)

# plot(main = "Overlay",
# 	type="l",
# 	col="#3182bd",
# 	xlab = "time [ms]",
# 	ylab = "Signal [mv]"
# 	)

maximum = 0
minimum = 0
for (i in 1:length(df)){
 	if (maximum < max(df[,i])){
 		maximum = max(df[,i])
 	}
	if (minimum > min(df[,i])){
		minimum = min(df[,i])
		
	}
 }

print(maximum)
print(minimum)

plot(df[,1], df[,2], main = "Overlay",
     type="l",
     ylim = c(minimum, maximum), 
     col=1,
     xlab = "time [ms]",
     ylab = "Signal [mv]"
     	)

for (i in 3:length(df)){
  lines(df[,1], df[,i], col=i)
}


