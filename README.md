# R'Chat
[![build on main](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/actions/workflows/main.yml/badge.svg)](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/actions/workflows/main.yml)

 > Authors:
- [Devin Shaw](https://github.com/DevinRShaw)
- [Mario Cuaya](https://github.com/mcuaya1)
- [Brian Byun](https://github.com/brianubyun)
- [Abraham Zambrano](https://github.com/StrickVax)
- [Mac Boyd](https://github.com/mboyd020)

## IMPORTANT
> This project was done with a group of people on a private repository provided by the school, thus mirroring the original repository to my own public repository contains only my branches.

## Project Description
 > * R'Chat is a chat room that runs on a server, authenticates, and accepts multiple clients at once, allowing clients to chat in real-time with each other. R'Chat keeps chat logs for later inspection by admin users.
>  * Discord is a common application that all of the team members use, which is a part of why we are interested in how programming for a chat application works. 
>  * Clients will run client executable, with terminal prompts for user authentication upon connection. Upon connection, client messages will be broadcast and received by other clients. On server side where the server was ran, it will have all messages sent listed. Client will disconnect upon specific user input format (//quit). Server will also terminate upon specific input format by a server admin (//exit). Client can also send some emojis to add more variation rather than just messages.
 > * Creating a client/server style chat room serves as an introduction to using C++ for socket programming and multithreading, both of which are important concepts in Embedded Systems, System Programming, Distributed Systems, and Cloud Computing. It is also a good exercise in using authentication methods and storing data. This project is also complex enough that it requires proper use of OOP concepts to keep code readable and scalable so it is great practice for us as students.
 > * This project is written in C++ and utilizes C++ tools such as CMake for ease of development. The functionality is supported by libraries for socket programming (networking), multithreading (multiple client handling), and file formatting for storing user credentials.
>  * Upon asking for authentication, user will be prompted with "Register(0) or Login(1):" and user can either input 1 or 0 depending on what they want to do.
>  * Upon successful login or registration, output with "Login successful!" or "Registration successful!" will be printed out respectively.
>  * Upon unsuccessful login or registration, output with "Username or password not recognized." or "This user already exists, please login instead." will be printed out respectively.
>  * Messages from other users will be displayed in the format "username: message contents"
>  * Specifically, once connected, the client can send messages as input to another client if they are connected to the server and the message sent as input will be the output for the other client connected.

## User Interface Specification
### Navigation Diagram
![navigation-graph drawio (1) drawio (1)](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/88609025/e1aca429-5433-4ced-91c9-f9f380410256)


### Screen Layouts
> All interactions will occur via a Linux bash shell terminal.
>
>  This is what the terminal will look like when you are prompted to choose authentication methods and input credentials
> 
> ![image 1](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/88609025/c79db8a9-e26e-4011-8560-20a7819b79ba)
> ![image,2](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/88609025/a5dab855-ed54-48cc-98d7-57f758ff4328)
> 
> This is what the terminal will look like when you are prompted to enter a message in the chat room.
> ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/7725059b-016f-442d-b2d6-1790e8511410)
>
> This is what the terminal will look like on the server side where all messages are sent.
> ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/a58a375a-e7b5-434f-ba03-c7192994abfe)
>
> This is what the terminal will look like on the server side when a client disconnects from the chat room.
> ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/3e531912-9a45-44da-b062-affaf7a027a3)
>
> This is what the terminal will look like when the user connects to the chat system and is asked to register (successful).
> ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/b709d257-c12c-4bea-ade0-3ffeefc3dbad)
>
> This is what the terminal will look like when the user connects to the chat system and is asked to log in (successful).
> ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/2dae652f-9467-4239-9bf1-817c591af790)


## Class Diagram
> ![oldold drawio](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/88609025/95ceda37-f2a5-48bd-9eb3-110bc317d5a8)

> * Server class instantiates a server object that uses socket programming and creates threads to handle server input and client connections.

> * ServerAuthenticator validates registration/login requests from Client Authenticator

> * Command Handler executes commands by listening in a thread for server-side input

> * Logger timestamps and records all messages sent to the server

> * Client class instantiates a client object that creates a connection to the server using sockets, server port, and server domain name. Also creates threads to handle sending and receiving messages from the server.

> * User class represents users as their username and password

> * UserCred class handles the input of user credentials in Client Authenticator

> * ClientAuth class sends username and password to the server, then prompts user based on server response

> * Emoji class deals with transferring messages into emojis (not shown in this UML since it is the old one; below is the updated UML).


## New Class Diagram with SOLID principles
![updatedupdateduml drawio](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/cf4355e8-932a-492e-bc3a-73c02c18f9ba)

> ##### What SOLID principle(s) did we apply?
> * One of the updates in our class diagram was the addition of a Client Command Handler class which applied the **single responsibility principle**. We applied it by creating a relationship with the Client class to handle all of the commands the client inputs via a "//..." format. This change helped us write better code by simplifying and making it easier to write unit tests as well as maintaining scalability if we ever want to add more commands in the future that the user can input.
> * Another update in our class diagram was the addition of the Emoji class which applied the **open closed principle**. We applied it by creating a relationship with the Client Command Handler class to handle all of the current and potential emojis that we are adding in the future via a "//[emoji_name]" format. This change helped us write better code by making the Client Command Handler open to extensions for all the emojis in the Emojis class we created, but closed for modification in the Client Command Handler class itself.
> * One other update we did that was already modified in the Phase II diagram after being acknowledged about the SOLID principles was creating a Logger class that follows the **single responsibility principle**. We applied it by creating a relationship with the Server class to handle the specific responsibility of just logging all messages sent in the chat room. This change helped us write better code by creating more clarity for what the responsibility of the Logger and the Server class is and possibly creating more member variables and methods within the Logger class itself to the file.txt.
> * Another update we did after learning about the SOLID principle to the Phase II diagram was separating the Server and Client class to not have any relationships which complies with the **interface segregation principle**. Doing this allowed the client side to not be forced to interact with any of the unneeded server commands that a client should not need. We applied it by essentially having two mini UMLs in one so the Server class can have its own relationships with other classes that follow the SOLID principles; the same for the Client class. This change helped us write better code by allowing for easier unit tests in the sense that we could test Client and Server class independently as well as for scalability as shown from the relationships with other classes.
> * Another update we did to the Phase II diagram prior was creating a UserCred class that follows the **dependency inversion principle**. Creating a UserCred class allowed for the User class and ClientAuth class to use UserCred as an abstraction to input credential/user info and not the User class just being dependent on ClientAuth. This change helped us write better code for unit tests since it created an abstraction that we could test independently from the other classes. Doing this also helped with the understandability and readability on what specific classes are meant to do. 
 
 ## Screenshots
 > Screenshot of input and output after running server executable to connect to port.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/899797d7-dd12-4472-8a7c-6d88acdf2341)
 
 > Screenshot of input and output after running registration for client. 
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/fb22854e-8dd4-4d67-9c36-36898e4563eb)

 > Screenshot of input and output after running successful login.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/a1691915-5e6e-4c86-8b27-64d3751c9361)

 > Screenshot of input and output after running the unsuccessful login.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/465d5f6a-0080-4db2-8249-c37c7b8c9c5e)

 > Screenshot of input and output after client registration, login, and sending messages which is broadcasted to the server along with the username.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/f4cbebfb-e4aa-4165-ad1b-66bfcdd30c01)

 > Screenshot of input and output of two clients logged in and connected to chat server and talking to each other.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/bc9f8d45-6c64-4a17-bec1-b26ed356e48c)

 > Screenshot of input and output of two clients logged in and connected to chat server and using emojis.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/ebceb948-0515-4589-9302-db1734597266)

 > Screenshot of input and output of client disconnecting from chat server via //quit.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/ccafdfd3-db86-475d-938f-b8fb810cf9f2)

 > Screenshot of input and output of server closing via //exit and all clients being disconnected as well.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/e4dddf0e-b53e-4e97-a7b9-bc25a05e9c38)

 ## Installation/Usage
 > To install and run our application, you will need to:
 - Git clone our repository via git clone <repos_link> inside the VSCode terminal (To get our repository link, go to the very top and click on the green code button and copy the HTTPS link given)
 - Inside the terminal, cmake . and make the CMakeLists.txt file to update all executables with the latest code changes and to be able to run all necessary executables
   - For dependencies, you will need:
     - googletest folder along with its submodules to compile all test and test files without any error
     - Terminal on VSCode that is able to run cmake . and make
     - Pretty recent VSCode version to not run into errors with some libraries within our code that was not implemented in versions prior to the current VSCode 
 - Run the server executable (./server_run) for the server to connect with the port 
 - Allow clients to connect to the server via the client executable (./client_run) in another terminal
   - If you are just running it by yourself but want to connect another client to see how messages are sent, you can open a new terminal on VSCode and run ./client_run in that terminal

 > From there, you can either:
 - Keep sending messages or emojis as a client to other clients that will be broadcast to the server side or you can quit the chat server via //quit
 - Close the server via server-side which would shut down all client connections and their respective client sockets via //exit

 ## Testing
 > Our project was tested/validated by creating unit tests to ensure that each component or unit of code that was added functions as expected via the Google test subfolder. Within our unit tests, we tested specific components such as the //quit command to disconnect a client from the chat server or the //exit command to shut down the server. We also tested if the server connected successfully to the port by testing if the server connected to the port on its own; the same with clients connecting to the chat server.

 > We also did regression testing to see if any changes in our code affected past unit tests that previously were successful. We did this with every addition we made to the code.

 > We also did integration testing to see if different classes or functions such as CommandHandler and Server/Client class worked as expected when they were integrated in the code.

 > We also did code reviews so whenever pull requests would be created, either the next sprint meeting we had as a group or with one other group member, we assessed the code to not have any merge issues or have any conflicts with successfully running the code as expected to minimize errors and validate each addition to the project.

 > We also used some CI aspects in our code to make sure that there was not any regression in our code. We did this by creating a workflow that runs cmake . and make to ensure that all executables inside our CMakeLists.txt are compiled with no error and all executables run as expected with no error.  

##

> I (Mac) had to use code from a few online sources. There are comments in the code with links to the sources as it comes up, but to make them easier to find, the links are also given below.
- https://stackoverflow.com/a/6326156
- https://stackoverflow.com/a/9732927
