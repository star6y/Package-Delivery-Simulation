# Package Delivery Simulation Extension


### General information:
Team number: Team-001-23
Members: Bao Ha (ha000045), Andrei Anicescu (anice002), Mohamed Ali (ali00429), Ubayd Sharif (shari147)


### Video Presentation
https://www.youtube.com/watch?v=C1ki0lYqM-g

## Docker Hub (Link)
- Our repo link:
  - https://hub.docker.com/r/arizonapurple/team-01-23-sim
  - This is the link to our docker image which is hosted on Docker Hub.
- Docker Hub is a cloud-based repository service that allows developers to host and maintain their docker images.
- A Docker image is a standalone package that includes everything needed to run a piece of software.

## How to run
- Ensure Docker is installed on your computer
- Ensure that the Docker Daemon is running
- Run the pull command
  - ```docker pull arizonapurple/team-01-23-sim```
- Run the docker container
  - ```docker run -p 8081:8081 arizonapurple/team-01-23-sim:latest```
- Access the application by visting http://localhost:8081/


## About this project
This project was an extension of a package delivery simulation. Currently, when the simulation is started, entities are created on the map. For now, we have the following entities: drone, human, and helicopter. A package can be scheduled for delivery in a different tab. The user selects two points: where the package will be picked up from, and the package's destination. After the delivery is scheduled, two new entities are added to the simulation: a package and a robot (customer). The drone now starts the process of completing this delivery. It uses a bee line strategy to go to the package. Before scheduling the delivery, the user was able to select a pathfinding strategy that the drone can use to move from the package's location to the customer’s. The drone uses this strategy to arrive at the destination.

The simulation was good so far, but it’s not realistic. To make it more realistic and interesting, we decided to add two extensions: a battery for the drone, and an entity subscription service. We would use a decorator design pattern to wrap a battery around the drone. When the battery’s charge gets too low, the drone would go charge at a charging station. To add charging stations, we used a factory method pattern to create these entities at the start of the simulation. Before the drone starts any delivery, it checks if it can make it all the way to the package, the destination, and the nearest charging station from the destination. If it cannot make this trip, it finds the charging stations closest to its position, and goes to it. Otherwise, the drone continues the delivery logic it employed previously. When needed, it travels to the charging station using a beeline strategy. Using this method allows us to simply find the distance between two points to calculate the distance of any trip.

Next, we worked on the entity subscription service. There is a publisher that publishes (sends info) to subscribers. The subscribers have to choose to subscribe to a certain publisher. All entities inherit from an entity interface, and the entity interface inherits from a publisher interface. This allows any entity to become a publisher, by calling the publisher's functions. For now, we subscribe to drones only. When the simulation sends an update message to all of the entities, the drone then publishes its name, the current battery status, activity, and what mode it’s in. The information published by the drone gets sent to the front end, so that the users can view the drone's information in real time. This would mean that the subscriber is the front end. However, the simulation model had to subscribe to the drone, and the simulation then pushes the published info to the front end.

The interesting part of this simulation is that it feels more realistic now. We can truly simulate package delivery scenarios, and see the results by checking the entity's status and battery percentage. 


## How to see these new features in action?

Load the simulation. On the left hand side, you will see a transparent window that covers the simulation. We will call this the notification bar. That is the information that the drone publishes. The front end is the subscriber. 

On the top right, you can choose which entity you want to view. Currently there are five charging stations to choose from. Click on one and the simulation view will center on it. You can also increase the speed of the simulation using the slider bar (but not to 0). To schedule a package, click the schedule button.

The notification bar shows how much battery the drone has left. Schedule a delivery (make it about half the width of the entire map). Watch the drone's battery decrease faster while it makes a delivery. When it reaches 15%, it will go to the nearest charging station. If you schedule deliveries, it will not go until it is fully charged.


## Sprint Retrospective

Our team used Jira to create sprints and divide work. Adding tasks to each sprint made us think about what it would take to complete each task, and how much time and consideration it needed. Jira allowed us to visualize our development plan. From there we divide tasks depending on scheduling needs, and implementation interest. Breaking the process into two sprints allowed us to move unfinished tasks of the previous sprint into the current one. Having two weekly meetings helped the team get on the same page about the project's direction and situation. Communicating over text and email allowed us freedom to work on the project at convenient times, and send updates to our teammates as needed.

## UML
[UML.pdf](https://github.umn.edu/umn-csci-3081-f23/team-001-23-hw4/files/1045/UML.pdf)

![UML](https://media.github.umn.edu/user/25144/files/1872d984-b7f0-463e-84ba-2ae2b3475d2e)


