# Student number:  
# Example for saving data to a file in OCTAVE

fid = fopen ("test1.txt", "w");
fdisp (fid, "100 + 50/2 is ");
fdisp (fid, 100+50/2);
fclose (fid);
