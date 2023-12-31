# Package Delivery Simulation Extension

## About this project
This project was an extension of a package delivery simulation. Currently, when the simulation is started, entities are created on the map. For now, we have the following entities: drone, human, and helicopter. A package can be scheduled for delivery in a different tab. The user selects two points: where the package will be picked up from, and the package's destination. After the delivery is scheduled, two new entities are added to the simulation: a package and a robot (customer). The drone now starts the process of completing this delivery. It uses a bee line strategy to go to the package. Before scheduling the delivery, the user was able to select a pathfinding strategy that the drone can use to move from the package's location to the customer’s. The drone uses this strategy to arrive at the destination.

The simulation was good so far, but it’s not realistic. To make it more realistic and interesting, we decided to add two extensions: a battery for the drone, and an entity subscription service. We would use a decorator design pattern to wrap a battery around the drone. When the battery’s charge gets too low, the drone would go charge at a charging station. To add charging stations, we used a factory method pattern to create these entities at the start of the simulation. Before the drone starts any delivery, it checks if it can make it all the way to the package, the destination, and the nearest charging station from the destination. If it cannot make this trip, it finds the charging stations closest to its position, and goes to it. Otherwise, the drone continues the delivery logic it employed previously. When needed, it travels to the charging station using a beeline strategy. Using this method allows us to simply find the distance between two points to calculate the distance of any trip.

Next, we worked on the entity subscription service. There is a publisher that publishes (sends info) to subscribers. The subscribers have to choose to subscribe to a certain publisher. All entities inherit from an entity interface, and the entity interface inherits from a publisher interface. This allows any entity to become a publisher, by calling the publisher's functions. For now, we subscribe to drones only. When the simulation sends an update message to all of the entities, the drone then publishes its name, the current battery status, activity, and what mode it’s in. The information published by the drone gets sent to the front end, so that the users can view the drone's information in real time. This would mean that the subscriber is the front end. However, the simulation model had to subscribe to the drone, and the simulation then pushes the published info to the front end.


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


## UML

![UML](https://media.github.umn.edu/user/25144/files/1872d984-b7f0-463e-84ba-2ae2b3475d2e)


