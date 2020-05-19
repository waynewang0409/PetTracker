# PetTracker
# PetTracker
## 1 System Design
### a. Architecture of the entire system     
PetTracker aims to provide pet owners with services such as tracking the location of pets, monitoring the health and activity status of pets, timely notification of pet health abnormalities, and providing the location and contact information of nearby pet hospitals.
The architecture is composed of M5Stack，Web application and Desktop application.     
**M5 stack to be used by pets.** It can locate the location of the pet, measure distance between the pet and owner, collect data from the pet and send it to the server.    
**Desktop to be use by clients.**   It can show the user's information, pet's status, action and location inforamtion which are sent by the server.    
**Web to be use by clients and developers.**    There are two kinds of web applications. One is for the client which has the same functions as the Desktop application, and the other is for the developer which can manage and take a look at the databases of uses and pets.

### b. Object-Oriented design of key sub-systems (e.g. Desktop Application, Web Application etc.)
**Desktop:**  
The Desktop focuses on data visualisation, management and control tasks for our application. Main efforts were put in designing the background pictures which show all contents of the applictaion.  Black circles are used to highlight the position of buttons, which is not very accurate because of the difficulty of fixing.Also, we try to make a clear version of how users can interact with the pages by clicking different buttons and make a process tree to show them.   
 ![image](https://github.com/PetTracker/PetTracker/blob/dev/Mobile%20application/Processing/prcess_tree.png)
**m5stack:**   
M5 stack is used to locate the location of the pet, measure distance between the pet and owner, collect data from the pet and send it to the web server. To fulfill these functions, we break M5 Stack into three parts to design. First, we get the gps raw data from M5 Stack, and we use Tiny GPS++ library to reproduce raw data into the data we can use. Those data include location, time, speed, satellite, and altitude. However, we only need location data, therefore we only display location on M5 Stack. Secondly, we use VL53L0X, which is the distance sensor, to measure the distance between pet and owner. We use millimeter to display the distance. Last but not least, we use MQTT to transfer our data. We send location and distance back to the web server, and server will process those data. When the server found out that the distance between pet and owner is too far away, the server will send a warning message through MQTT to M5 Stack. When M5 Stack get the message from the server, we use NOTE_DH2 to make warning sound. Through those steps, we can make sure the pet will not get lost when they are taking a walk.    
**web:**   
(1)For clients:   
(2)For developers:    


### c. Requirements of key sub-systems (in the form of selected user stories)
（1）As a pet owner, I can use my mobile phone or webpage to check the location of my pet, so as to prevent my pet from leaving the safe area when I am not at home.       
（2）As a pet owner, I can use my mobile phone or webpage to check whether the health index data of my pet is within the normal range, and can be reminded in time when the health index of the pet is abnormal, and can contact the hospital in time after being reminded, so as to ensure the health of the pet to the maximum extent.      
（3）As a pet owner, when I am not around my pet, I can use my mobile phone or web page to check the status of the dog (such as running, lying, etc.), so as to better understand the dog's life.         
（4）As a dog owner, I can see the location of my friends in the neighborhood when I walk my dog, so that my dog can have a good social relationship.         
（5）As a pet owner, I will go to the hospital regularly for physical examination of pets. I hope to see the grading, evaluation and geographical location of each pet hospital before I go to the pet hospital, so that I can choose the pet hospital more conveniently.       
### d. The evolution of UI wireframes for key sub-systems
**Paper prototyping:**  
![image](https://github.com/PetTracker/PetTracker/blob/dev/gif/Paper%20prototyping.GIF)         
**Final product:**      
![image](https://github.com/PetTracker/PetTracker/blob/dev/gif/final%20product.GIF)

### e. Details of the communication protocols in use (including a rational for your choice)
### f. Details of the data persistence mechanisms in use (including a rational for your choice)
### g. Details of web technologies in use (including a rational for your choice)

## 2 System Implementation
### a. Breakdown of project into sprints (showing the users stories implemented in each).
### b. Details of how you evaluated your designs (techniques used & awareness of their limitations)
### c. Discussion of Social and Ethical implications of the work

## 3 Project Evaluation
### a. Reflective discussion of the success of the project
### b. Discussion of future work (in terms of design, development and evaluation)
### c. Reflect on the working practices of your group, how well they did or did not work, e.g, management of issues, communication, Agile (etc).
### d. This is a chance to reflect on how coronavirus has affected your project (remote working practices etc)
