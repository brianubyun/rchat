# R'Chat

 > Authors:
- [Devin Shaw](https://github.com/DevinRShaw)
- [Mario Cuaya](https://github.com/mcuaya1)
- [Brian Byun](https://github.com/brianubyun)
- [Abraham Zambrano](https://github.com/StrickVax)
- [Mac Boyd](https://github.com/mboyd020)

## Project Description
 > * R'Chat is a chat room that runs on a server, authenticates, and accepts multiple clients at once, allowing clients to chat in real-time with each other. R'Chat allows admin users to moderate clients and keeps chat logs for later inspection by admin users.
>  * Discord is a common application that all of the team members use, which is a part of why we are interested in how programming for a chat application works. 
>  * Clients will run client executable, with terminal prompts for user authentication upon connection. Upon connection, client messages will be broadcast and received by other clients. Client will disconnect upon specific user input format. Server will also terminate upon specific input format by a server admin.
 > * Creating a client/server style chat room serves as an introduction to using C++ for socket programming and multithreading, both of which are important concepts in Embedded Systems, System Programming, Distributed Systems, and Cloud Computing. It is also a good exercise in using authentication methods and storing data. This project is also complex enough that it requires proper use of OOP concepts to keep code readable and scalable so it is great practice for us as students.
 > * This project is written in C++ and utilizes C++ tools such as CMake for ease of development. The functionality is supported by libraries for socket programming (networking), multithreading (multiple client handling), JSON file formatting for storing user credentials.
>  * Upon asking for authentication, user will be prompted with "Register(0) or Login(1):"
>  * Upon successful login or registration, user will be prompted with "Login successful!" or "Registration successful!" respectively.
>  * Upon unsuccessful login or registration user will be prompted with "Username or password not recognized." or "This user already exists, please login instead." respectively.
>  * Messages from other users will be displayed in format "<username>: message contents"

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

> * The server class instantiates a server object that uses socket programming and creates threads to handle server input and client connections.

> * Server Authenticator validates registration/login requests from Client Authenticator
>
> * Command Handler executes commands by listening in a thread for server-side input

> * Logger timestamps and records all messages sent to the server

> * Client class instantiates a client object that creates a connection to the server using sockets, server port, and server domain name. Also creates threads to handle sending and receiving messages from the server.

> * User class represents users as their username and password

> * User Credentials class handles the input of user credentials in Client Authenticator

> * Client Authenticator sends username and password to the server, then prompts user based on server response


## New Class Diagram with SOLID principles
> ![newnew drawio](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/88609025/c2634155-70f6-4342-983f-fd768ae87b64)

> ##### What SOLID principle(s) did we apply?
> * One of the updates in our class diagram was the addition of a Client Command Handler class which applied the **single responsibility principle**. We applied it by creating a relationship with the Client class to handle all of the commands the client inputs via a "//..." format. This change helped us write better code by simplifying and making it easier to write unit tests as well as maintaining scalability if we ever want to add more commands in the future that the user can input.
> * Another update in our class diagram was the addition of the Emoji class which applied the **open closed principle**. We applied it by creating a relationship with the Client Command Handler class to handle all of the current and potential emojis that we are adding in the future via a "//[emoji_name]" format. This change helped us write better code by making the Client Command Handler open to extensions for all the emojis in the Emojis class we created, but closed for modification in the Client Command Handler class itself.
> * One other update we did that was already modified in the Phase II diagram after being acknowledged about the SOLID principles was creating a Logger class that follows the **single responsibility principle**. We applied it by creating a relationship with the Server class to handle the specific responsibility of just logging all messages sent in the chat room. This change helped us write better code by creating more clarity for what the responsibility of the Logger and the Server class is and possibly creating more member variables and methods within the Logger class itself to the file.txt.
> * Another update we did after learning about the SOLID principle to the Phase II diagram was separating the Server and Client class to not have any relationships which complies with the **interface segregation principle**. Doing this allowed the client side to not be forced to interact with any of the unneeded server commands that a client should not need. We applied it by essentially having two mini UMLs in one so the Server class can have its own relationships with other classes that follow the SOLID principles; the same for the Client class. This change helped us write better code by allowing for easier unit tests in the sense that we could test Client and Server class independently as well as for scalability as shown from the relationships with other classes.
> * Another update we did to the Phase II diagram prior was creating a UserCred class that follows the **dependency inversion principle**. Creating a UserCred class allowed for the User class and ClientAuth class to use UserCred as an abstraction to input credential/user info and not the User class just being dependent on ClientAuth. This change helped us write better code for unit tests since it created an abstraction that we could test independently from the other classes. Doing this also helped with understandability and readability on what specific classes are meant to do. 
 
 > ## Final deliverable
 > All group members will give a demo to the reader during lab time. ou should schedule your demo on Calendly with the same reader who took your second scrum meeting. The reader will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Project board.
 > * Make sure your README file and Project board are up-to-date reflecting the current status of your project (e.g. any changes that you have made during the project such as changes to your class diagram). Previous versions should still be visible through your commit history. 
 
 ## Screenshots
 > Screenshot of input and output after running registration. 
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/fb22854e-8dd4-4d67-9c36-36898e4563eb)

 > Screenshot of input and output after running successful login.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/a1691915-5e6e-4c86-8b27-64d3751c9361)

 > Screenshot of input and output after running the unsuccessful login.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/465d5f6a-0080-4db2-8249-c37c7b8c9c5e)

 > Screenshot of input and output after client registration, login, and sending messages which is broadcasted to the server.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/38fca312-b668-42e5-9837-5c1ccf69e374)

 > Screenshot of input and output of two clients logged in and connected to chat server and talking to each other.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/bd142e38-827c-472e-9d6a-e69c57d04499)

 > Screenshot of input and output of client disconnecting from chat server via //quit.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/a0a9ba10-e3b2-468d-a013-59718ccc0b47)

 > Screenshot of input and output of server closing via //exit and all clients being disconnected as well.
 > ![image](https://github.com/cs100/final-project-azamb015-dshaw013-bbyun004-mcuay001-mboyd020/assets/146309310/9ef9a000-2f66-4728-ae3d-8a25134d0adf)

 ## Installation/Usage
 > To install and run our application, you will need to first:
 -  
 > Instructions on installing and running your application
 ## Testing
 > Our project was tested/validated by creating unit tests to ensure that each component or unit of code that was added functions as expected via the google test subfolder. Within our unit tests, we tested specific components such as the //quit command to disconnect a client from the chat server or the //exit command to shut down the server. We did this to ensure that the server connected and ran successfully with a specific port and the same for clients with their specific client sockets.
 
 > We also used some CI aspects in our code to make sure that there was not any regression in our code. We did this by creating a workflow that connected to the server and went through baseline tests to ensure everything ran correctly.
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
