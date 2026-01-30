# This Script generates white noise using the rand() function
# The white noise is saved in a file "white_noise_sound.wav"
# Execution time is measured
# A histogram displaying the first 100 samples is then displayed

# NOTE ABOUT FUNCTION DEPRECATION
# Please read the wiki about writing audio in Octave 5.1+ 
# wiki.ee.uct.ac.za/Octave

tic; white = rand(48000*1000, 1)*2 - 1; runtime = toc();

# On Octave<5.1, use wavwrite. On >=5.1, use audiowrite
#wavwrite(white, 48000, 16, 'white_noise_sound.wav');
#audiowrite('w.wav', white, 48000, 'BitsPerSample', 16);

disp(strcat("It took: ", num2str(runtime*1000), " ms to run"));
hist(white, 100, 1);
