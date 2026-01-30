
#Author: ?????

using Pkg

#_____________Uncomments the packages below once they have been installed________
#using WAV
#using Plots
#using TickTock
#using Statistics

#this function installs all packages needed to run this script
function installFunc()
	Pkg.add("WAV")
	Pkg.add("Plots")
	Pkg.add("TickTock")
	Pkg.add("Statistics")
	print("------Packages Installed---------")
	print(Pkg.status())
end


function main()
	installFunc() #comment this out once you have run it once and all packages have been installed
	
	
end

main()
