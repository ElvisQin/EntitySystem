Welcome
==========
An Entity Component System framework based on Cocos2d-x, now the supported version is 3.0 beta2.


1,how to run?
-------------
you need download the Cocos2d-x 3.0 beta2 sourcecode from the offcial repository,please fllow this link:
https://github.com/cocos2d/cocos2d-x 

then put the 'cocos2d' directory from the Cocos2d-x sourcecode into the position same as 'Classes' directory.


2,how to use?
---------------
1. create an Entity: ECSmanager::createEntity(); 
2. create you own Component which should be a subclass of ECS::Component , such as 'MyComponent'
3. create you System which should be a subclass of ECS::System
4. init the ECSManager: auto ecs=new ECSManager();
5. put all your system: ecs->addSystem(mySystem);
6. add component to Entity: ecs->addComponentToEntity(myComponent,myEntity);
7. call the update methed of ECSManager in your gameloop, such as the visit or update method of HelloWorldScene.
8. that's it!
  
  
3,discussion
-------------
you may leave a message at my blog: http://elvisco.de


4,please enjoy this.
-------------------
