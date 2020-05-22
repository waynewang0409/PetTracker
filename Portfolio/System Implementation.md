##  System Implementation
### a. Breakdown of project into sprints (showing the users stories implemented in each).
#### 1st
We chose to develop our application with p5.js since it’s a fit for what we are developing.
Design: We drew out what we could do and a basic structure for our application and the icon of our app. The main purpose of our logo is to show users simply why they’re using this app. Therefore, its design is a head of a dog since our app is mainly designed for pets, especially dogs.
Code: To create a basic foundation of our application, we set up basic pages through p5.js.
Test: After further trials, we will be able to develop specific parts of our application.

**Desktop Analysis:**
Building a basic desktop application and knowing what we’re going to do with MQTT is what we did at this stage of work.

**M5Stack Analysis:**
Making M5Stack able to connect to Wi-Fi and transmit messages, also part of UI design. We tested with various types of network and some of them required specific MAC addresses. To make sure it’s able to connect with all of them, we tried a variety of addresses.

#### 2nd
**Web Analysis:**
We considered which kind of settings we want to put on the first page of our app. The first thing came to our minds were making sure the pet doesn’t leave the safe zone when the owner wasn’t home.
Design: Basic functions is what we focused on at this moment, the perfection of design wasn’t our first priority. Therefore, we created the homepage with basic categories on it.
Code: Besides JavaScript and HTML for fundamentals. Creating buttons for various kinds of functions is important to our application. For example, we are not only tracking locations of pets but also pet’s vitals and see if they’re normal and will be notified if there’re not normal and contact hospital or other facilities immediately. Thus, we chose p5. play library because it provides control of visual objects which we used the most in our application.
Test: To connect each pages smoothly with user hitting buttons and check if there’re any malfunction in it.

**Desktop Analysis:**
We decided to save our data as JSON files directly instead of creating another database. Not only just to save an extra construction but also JSON is a type of file that integrates with other platforms well.
Also, we add a database and four API, these API are responsible for reading User names and code, checking it with those stored in the database, searching user’s pet by Machine Code and use the code to check on pet’s status

**M5Stack Analysis:**
We added parsing function for JSON since all our files are stored in this type of file and tested. At the same time, we enhance our UI design from what we built last time. Our messages could be translated into variables successfully after tested. The code is able to meet our goal at this stage.

#### 3rd
**Web Analysis:**
We consider it better to add on more function to enrich our application. For example, users can see if there’re other dogs around through application, this function allows pets and its owners to build social network with others, but it’s still an extra concept.
Code: we were looking at p5. sound to add audio output, which is for the buzzer in our system.
Test: After we implemented this part, we tested under different situations using our application to make sure everything’s working fine.

### b. Details of how you evaluated your designs (techniques used & awareness of their limitations)
**Unit and Integration testing:**	
At the very beginning, unit testings were carried on by various individual designers, especially focusing on code quality. Various JSON objects were created to test different situations that can happen anytime based on the web application, M5stack, and processing part. After we finished the main part of our project, we start to check the coherence and relevance between different parts of our projects to fix the problems we faced as well as further expand our function.

**User stories:**
Various user stories were designed to test the efficiency and completeness of our project. The first one was designed when we finished the main process of the mobile app. After that, we found out several problems. For example, a user can only log in to the app when he/she already has the account. To fix that, we add a register page to enable the new users to create the account. At the same time, we also add some functions such as providing hospital details, creating a pet society to make our app a more useful one.

**Online investigation:**
After we finished our project, an online link (https://run.mockplus.cn/tr9rfhERR8zcImc1/index.html) which related to the mobile app was created to demonstrate the complete process of our project. We delivered it to some potential users such as our classmates and relatives who own pets. Meanwhile, a structured interview was designed to find out the subjective response and satisfaction of the participants. After we collected their feedback, we make a quantitive analysis to find out somewhere that we can better be designed, for example, we changed the design of our main page from descriptive text to icons to make the page more clear.

**Limitations**
Due to the COVID situation, limited user studies were carried on, which lead to a limited amount of user feedback we collected. Also, because of the lack of face-to-face communication with potential users and investors, our design still has a long way from going public. Besides, cross-testing cannot be carried on due to the current situation and the design details of different parts can not be understood clearly by team members, which leads to insufficient integration testing.

### c. Discussion of Social and Ethical implications of the work
The Association for Computing Machinery (ACM) Code of Ethics and Professional Conduct provides general guidelines ensuring products or operations aimed at society’s greater goods.

#### Trials (Transparency & Prior info)
When our system is set to go onto a further stage, we will need to implement more trials to adjust, make sure current system is working at a level of low error rate or collecting data. Even most trials are simply related to pets, we still need to provide owners with overall participant information which assures these trials transparency.

#### Data Security (Public source code)
Using open sources on the internet to develop our program is convenient but leaves us the problem of easy for public access, anyone could enter our databases or system easily. Therefore, there’re improvements to be done, modifying the code to our own version is what has to be done in the long term.
But in the short term, there’re risks we have to monitor closely.

#### Privacy
When the program is being tested, we will have to store lots of user’s (pets) data and payment data or other sensitive data. Therefore, anonymity is something we can implement to protect our clients personal detail.

**Environmental impact**
Our program isn’t going to cause environmental impact, but if we have to consider any part of it will have the possibility of causing one, it’s the process of manufacturing the device for pets.
