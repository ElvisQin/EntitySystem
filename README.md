Hi,this project will not be maintained
==========
because I have started a new open source project named Genius-x. Genius-x has all features about ECS, moreover, it  will add more features such as FTUE,task system, custom format resources management and load synchronous. Please refer to: http://genius-x.org 


Welcome
==========
An Entity Component System framework based on Cocos2d-x, now the supported version is 3.0 beta2.


How to run?
-------------
You need download the Cocos2d-x 3.0 beta2 sourcecode from the offcial repository, please follow this link:
https://github.com/cocos2d/cocos2d-x 

then put the 'cocos2d' directory from the Cocos2d-x sourcecode into the position same as 'Classes' directory.


Feature
---------
1. based on the Origin Entity Component System idea(Decoupbe the system from component,this make it diff from Component-based design).
2. automatic attching system to Entity,you only need concern component.So,
3. it's data-driven.
4. better performance,we make every Entity has it's own System instance,but still keep auto-attaching,you do not need care about System.
5. lua and javascript binding support.(progress....)
6. system ordered.

How to use?
---------------
1. create an Entity: ECSmanager::createEntity(); 
2. create you own Component which should be a subclass of ECS::Component , such as 'MyComponent'
3. create you System which should be a subclass of ECS::System
4. init the ECSManager: auto ecs=new ECSManager();
5. put all your system: ecs->addSystem(mySystem);
6. add component to Entity: ecs->addComponentToEntity(myComponent,myEntity);
7. call the update methed of ECSManager in your gameloop, such as the visit or update method of HelloWorldScene.
8. that's it!
  
  
Discussion
-------------
you may leave a message at my blog: http://elvisco.de


Please enjoy this.
-------------------
