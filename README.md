# Overview

This is a simple project that I decided to do in C++ to better my skills in the language and 
to learn more.

The Project is a simple messaging system through the terminal / command line
Users can simply create a new accont, send and view messages and can actually delete all messages saved. The messages sent are stored in a csv file named "messages.csv". When the user requests to view all of the messages, the program reads the "messages.csv" file, reads it by row and recognizes that the first section (before the first comma) is the user that sent the message, the second section is the message, and the third is the date time that it was sent.

I wanted to write this program to understand c++ better and get more experience with the language. I also plan on building an app soon that will have a message board so doing this project helped me understand more of what I'd want to do and how I would begin implementing it. 


[Software Demo Video](https://youtu.be/uoXhPEvmcYA)

# Development Environment

I used VSCode to complete this project.

There were a few libraries that I used in this project:
* boost - to use the to_lower() function for the usernames
* fstream - for reading / writing files
* nlohmann - for working with json files
* ctime - to get the time

# Useful Websites

* [W3Schools](https://www.w3schools.com/CPP/default.asp)
* [tutorialspoint](https://www.tutorialspoint.com/cplusplus/index.htm)

# Future Work

* Move the stored messages to a database
* Host program on Heroku to allow for multiple users to use this
* Add a simple interface for the users. 