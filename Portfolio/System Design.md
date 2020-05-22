## System Design
### a. Architecture of the entire system     
   PetTracker aims to provide pet owners with services such as tracking the location of pets, monitoring the health and activity status of pets, timely notification of pet health abnormalities, and providing the location and contact information of nearby pet hospitals.
The architecture is composed of M5Stack，Web application and Desktop application.     
**M5 stack to be used by pets.** It can locate the location of the pet, measure distance between the pet and owner, collect data from the pet and send it to the server.    
**Desktop to be use by clients.**   It can show the user's information, pet's status, action and location inforamtion which are sent by the server.    
**Web to be use by clients and developers.**    There are two kinds of web applications. One is for the client which has the same functions as the Desktop application, and the other is for the developer which can manage and take a look at the databases of uses and pets.

### b. Object-Oriented design of key sub-systems (e.g. Desktop Application, Web Application etc.)    
   basic architecture of object oriented design:       
![image](https://github.com/PetTracker/PetTracker/blob/dev/gif/structure.jpg)         
         
**Desktop:**  
    This part focuses on data visualisation, management, storage and control tasks for our application. Efforts were put in designing the background pictures which show all contents of the applictaion. Black circles are used to highlight the position of buttons, which is not very accurate because of the difficulty in fixing.Also, we try to make a clear version of how users can interact with the pages by clicking different buttons and make a process tree to show the logic within them.Four functions have been written to show the interaction with information stored in local database. However, they haven't been embedded into the pages because of the difficulties in positioning.       
**m5stack:**   
    M5 stack is used to locate the location of the pet, measure distance between the pet and owner, collect data from the pet and send it to the web server. To fulfill these functions, we break M5 Stack into three parts to design. First, we get the gps raw data from M5 Stack, and we use Tiny GPS++ library to reproduce raw data into the data we can use. Those data include location, time, speed, satellite, and altitude. However, we only need location data, therefore we only display location on M5 Stack. Secondly, we use VL53L0X, which is the distance sensor, to measure the distance between pet and owner. We use millimeter to display the distance. Last but not least, we use MQTT to transfer our data. We send location and distance back to the web server, and server will process those data. When the server found out that the distance between pet and owner is too far away, the server will send a warning message through MQTT to M5 Stack. When M5 Stack get the message from the server, we use NOTE_DH2 to make warning sound. Through those steps, we can make sure the pet will not get lost when they are taking a walk.    
**web:**   
    (1)For clients:    
      This part is a web version of Desktop. What's more, it can also send a message to the M5Stack through MQTT when pets are abnormal.     
    (2)For developers/service providers:           
      This part is used to import and manage data repository. Functions have been written to show data on web by reading files, and highlight those abnormal heart rates.        


### c. Requirements of key sub-systems (in the form of selected user stories)
 （1）As a pet owner, I can use my mobile phone or webpage to check the location of my pet, so as to prevent my pet from leaving the safe area when I am not at home.     
  Requirements of M5Stack : send location information of pets to server            
  Requirements of Web for clients or Desktop: get location information of pets from server        
（2）As a pet owner, I can use my mobile phone or webpage to check whether the health index data of my pet is within the normal range, and can be reminded in time when the health index of the pet is abnormal, and can contact the hospital in time after being reminded, so as to ensure the health of the pet to the maximum extent.       
  Requirements of M5Stac: send health information of pets to server         
  Web for clients or Desktop: get health information of pets from server / get a message if health index is abnormal       
  Requirements of Web for developers: get a message if there is any abnormal health index              
（3）As a pet owner, when I am not around my pet, I can use my mobile phone or web page to check the status of the dog (such as running, lying, etc.), so as to better understand the dog's life.         
  Requirements of M5Stack: send action information of pets to server             
  Requirements of  Web for clients or Desktop: get action information of pets from server            
（4）As a dog owner, I can see the location of my friends in the neighborhood when I walk my dog, so that my dog can have a good social relationship.         
  Requirements of M5Stack: send location information of pets to server                       
  Requirements of Web for clients or Desktop: add other pets as friends / get location information of friend pets from server           
（5）As a pet owner, I will go to the hospital regularly for physical examination of pets. I hope to see the grading, evaluation and geographical location of each pet hospital before I go to the pet hospital so that I can choose the pet hospital more conveniently.       Requirements of Web for clients or Desktop: show hostital information  such as grading, evaluation and geographical location         
（6） As a pet ownner, whenever I log in, I can get or change information about myself and my pet such as names, ages and so on. What's more, I can also add or delete a pet.        
  Requirements of Web for clients or Desktop: register / log in  /  add pets / delete pets / modify owner or pet information / update files which store information function                  
  Requirements of Web for developers: manage files which store information   

        
### d. The evolution of UI wireframes for key sub-systems
**For clients:**           
    (1)Paper prototyping               
      At the beginning, we used a paper prototype to design the UI. It could enable the team to quickly integrate, modify, and present our ideas and product logic, which was convenient for our subsequent application design.                 
![image](https://github.com/PetTracker/PetTracker/blob/dev/gif/Paper%20prototyping.GIF)            
    （2）Processing Prototype                 
      Next, we used mockplus, a prototype design tool, to design UI for clients. We chose pink as the background color of the app, and the buttons were represented by simple icons. We also used Processing to design button actions and simulate interaction.                    
![image](https://github.com/PetTracker/PetTracker/blob/dev/gif/final%20product.GIF)                      
mind Mapping for the interaction:                     
![image](https://github.com/PetTracker/PetTracker/blob/dev/Mobile%20application/app/prcess_tree.png)  

**For developers:**           
    The developer's web page is only two pages, which are very simple. We mainly used the Bootstrap css framework for design and implementation.                   

### e. Details of the communication protocols in use (including a rational for your choice)
   We simply select MQTT to connect all our platforms because most of our communication won’t be information crowded, just simple command.
   When information is inputted, JSON file was read by the M5Stack and it started to apply what it was written to do.
   This method works for our application at the current stage, but if we consider more elements, like the future of this application, our data isn’t secured enough due to it’s a development from open sources.
   Therefore, when we need higher security level or each transmission contains more data, a more complicated communication protocol will be needed. 

### f. Details of the data persistence mechanisms in use (including a rational for your choice)
   M5Stack is used to sending out commands in our system, because it doesn’t have enough space to work as storage for data
   At first, we were thinking about building a database through MySQL, but it’s not as direct as JSON and it’s not a secure way to preserve sensitive data such as user’s information or GPS locations.
   Therefore, we chose JSON object arrays to hold our data since it’s compatible with a variety of webs and it’s able to be parsed on most devices.
   When a new array was created, information stored in the arrays will be called once the pet ID entered, bringing out data the system required.

### g. Details of web technologies in use (including a rational for your choice)
   We used HTML and JavaScript as the core of our program. While HTML is responsible for running pages in browsers, JavaScript make sure the website is responsive.
   Using p5.js is not only giving us more variety in designing our application but also easier access for everyone.
 
   The p5. clickable library, p5. play library were used for our buttons, enabling us to create multiple buttons and their design. The desktop app used the MQTT library to connect and it linked our four platforms.
