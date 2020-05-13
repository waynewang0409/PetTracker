# PetTracker
# PetTracker
## 1 System Design
PetTracker aims to provide pet owners with services such as tracking the location of pets, monitoring the health and activity status of pets, timely notification of pet health abnormalities, and providing the location and contact information of nearby pet hospitals.
### a. Architecture of the entire system
The architecture is composed of:  **Desktop application, Web application, M5Stack.**  
**Desktop:**  
The Desktop focuses on data visualisation, management and control tasks for our application. Main efforts were put in designing the background pictures which show all contents of the applictaion.  Black circles are used to highlight the position of buttons, which is not very accurate because of the difficulty of fixing.Also, we try to make a clear version of how users can interact with the pages by clicking different buttons and make a process tree to show them.   
**m5stack:**   
M5 stack is used to locate the location of the pet, measure distance between the pet and owner, collect data from the pet and send it to the web server. To fulfill these functions, we break M5 Stack into three parts to design. First, we get the gps raw data from M5 Stack, and we use Tiny GPS++ library to reproduce raw data into the data we can use. Those data include location, time, speed, satellite, and altitude. However, we only need location data, therefore we only display location on M5 Stack. Secondly, we use VL53L0X, which is the distance sensor, to measure the distance between pet and owner. We use millimeter to display the distance. Last but not least, we use MQTT to transfer our data. We send location and distance back to the web server, and server will process those data. When the server found out that the distance between pet and owner is too far away, the server will send a warning message through MQTT to M5 Stack. When M5 Stack get the message from the server, we use NOTE_DH2 to make warning sound. Through those steps, we can make sure the pet will not get lost when they are taking a walk.    
**web:**  


### b. Object-Oriented design of key sub-systems (e.g. Desktop Application, Web Application etc.)

### c. Requirements of key sub-systems (in the form of selected user stories)
e.g. “As a <role or persona>, I can <goal/need> so that <why>”    
**Desktop:**  
**m5stack:**   
**web:**  
### d. The evolution of UI wireframes for key sub-systems
**Paper prototyping:**  
**Processing Prototype:**   
  
**Final product::**  
[link video]
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
