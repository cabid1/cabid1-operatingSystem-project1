[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/OHwIpFF9)
# Project 1
Answer these questions please:

Project Overview:
-----------------------------------
What is the project about? Provide a brief overview that includes the project's name, purpose, and target audience.
the project is about creating a shell the projects name was project 1 and code for it can be found in 
simple_shell.c from my understanding it was to get us exposed to using c i learned syntax of c how to 
open files read and write to them 
how to get data from user and parse through it 
how malloc and realloc works
and how to use fork
Solution Approach:
------------------------------------------------------------

How did you approach the problem? Outline the steps or phases in your project development process?
i did not approach this well to be honest 
i would write a function test it by itself on a seprate ide (bad idea)
then add it to the code rather than running 
it all together which made fixing bugs a headache
in the future i want to do more incremental testing
to actually see if things work well together

but overall i worked down the list in the main_template
one day i worked on the main func started on the user prompt and 
finished up with the get_user_command

the next day i worked on parsing

then i worked on the execute 

then i finished up the functionality of the prompt and implemented helper functons 

then did the history (im not sure if this works as expected but it is reading in user commands)
 
then debugged 

Challenges and Solutions?
---------------------------
What challenges did you encounter while completeing your project, and how did you overcome them?

the main challenge i encountered was malloc and realloc in the online compiler it did not care 
if the var was set to realloc or not and so it passed tests with flying colors i also realized i had to set the end to /0 
or it was set to garbage data i found that out via debuging
gl does i also had problem freeing the data
i added a bunch of print statements to verify things were as it was supposed to be 
i wasnt sure how to approach fork things but looked at the prof examples and found one that was pretty close
there may have been more but i prob commented about it in commits or in gen comments i made silly mistakes 
and after testing some thing learned and fixed them



LLM Disclosure
--------------
Are there any external resources or references that might be helpful?
yes if i used a source i included a link to it above the function or in the comments 
in the comments and tried to explain what it was used for  

Testing and Validation
-----------------------
Testing Methodology: How did you test your project? Discuss any unit tests, integration tests, or user acceptance testing conducted.
Are there any specific commands or scripts that should be known?

for things like get user command and parse command i would write the function in a online compiler
then in main i would give it a test string and with the return i would loop through and print it out to check 
it was in the right format

for execute there wasnt much to test because i consulted the professors example and from the comments 
in the template i knew i had to add execvp and waitpid so if that wasnt working i more so blammed my parsing

i also added two helper func i started them in a online compiler
from the lecture i knew we just had to read them from the files so i looked into how to read files in c
i first gave input to concat two strings such as /proc and /cpuinfo and printed it out 
when i got the desired output i then moved to display and sent the concat string and outputed the files line by line
and checked with the example that it was right

overall i did testing HORRIBLY
when i put everything together i had to add so much print statements to verify data was correct 
and to find a sigfault which ended up being how i was comparing strings
i think i left some in the file and commented it out so you could see how some things were tested

Example session
---------------
Provide examples on running your project
to start run make then ./simple_shell
for things like ls, ls -ls, pwd at the prompt of ">>" type in such as ">>ls"
for things like /proc at the prompt of ">>" type in such as ">>/proc /cpuinfo"
for history at the prompt of ">>" type in such as ">>history"
