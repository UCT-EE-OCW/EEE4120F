
#How To Install Julia
Step 1) Go to the website: https://julialang.org/downloads/

Step 2) Install Julia

For Ubuntu:

step 3) Run julia using the file /bin/julia

Make a symbolic link (terminal): sudo ln -s /juliasDirectoryOnYourComputer/bin/julia /usr/local/bin/julia
if the above command doesn't work try: sudo ln -s ~/juliasDirectoryOnYourComputer/bin/julia /usr/local/bin/julia

#How To Run a Julia script
Provided you have created the symbolic link correctly you can run the scrpit by entering julia in terminal followed by the your script directory (eg  julia helloWorld.jl  )

#Installing the packages required in this script
The program includes the installFunc() which will install all the required packages. After these packages have been install uncomment the packages used in the script.
