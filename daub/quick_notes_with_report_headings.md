---
title: Quick notes with report headings
author: Niklas Blomqvist, Robin Gustafsson
geometry: margin=2.5cm
header-includes:
   - \DeclareUnicodeCharacter{00A0}{~}
---


\newpage


| Version | Date       | Sign off      | Change note                           |
|---------|------------|---------------|---------------------------------------|
| 0.1     | 2015-02-23 | Robin, Niklas | Quick jots                            |
|         |            |               | http://www.ida.liu.se/edu/ugrad/thesis/instructions/Exjobb_anvisning.pdf |


#Abstract
Customizations of the functionality (options) are often requested by the 
customer and have to be acknowledged in the manufacturing process of fork lifts.
When new options have to be created or present option algorithms have to be modified in 
the main software the complexity increses, the firmware revision pool gets
large and with the increasing code size the memory limit is threatened.
This affects the software development since the frequent development of the 
option handler is very resource consuming. Therefore it is desireble to have a 
very modular system for the option handler to simplify the development process. 
Although the market value of this improvement is neglecteble the possible long
term savings is the desireble effect. This thesis explores the posibility of 
migrating the option handling software to a separate hardware module to help the 
development process by effectivly increasing the modilarity of the system 
architecture.

(fyll på mer om uppnått resultat efter projektet)
The terms of inclusion and the tools to accomplish this 
option handler is analyzed. A system modell of the resulting approach will be 
designed and a prototype will be developed to validate the result.

_"En sammanfattning (abstract) ska kort och koncist beskriva och motivera det studerade_
_problemet, metoden samt resultat och slutsatser. Arbetets bidrag till_ 
_huvudområdet ska tydligt framgå. Vad är det rapporten säger om huvudområdet_ 
_som vi inte visste tidigare? Exempel på bidrag kan vara vilken effekt en_
_specifik algoritm eller programutvecklingsmetod får i en specifik tillämpning._
_Normalt ska en sammanfattning vara högst 150 ord, och inte innehålla några_ 
_referenser eller radbrytningar."_


#Introduction
We have conducted our thesis work at a big fork lift manufacturer located in
Östergötland. We have been asked not to call it by name in text. In this report
it will be called "The company".

##Motivation


_Här ska det studerade problemet översiktligt beskrivas och sättas in i ett_
_sammanhang som gör det tydligt att det är intressant och viktigt att studera närmare._
_Målsättningen är att göra läsaren intresserad av arbetet och skapa en vilja att läsa vidare._

##Purpose
In order to satisfy the customer demand of new features (options), The company 
needs a faster, more reliable and testable way to develop them. Now, options are 
added to the main firmware. This creates the problem where many branches of the 
firmware has to be created and it gets more difficult and time consuming to 
create patches and updates.

This thesis work aims to decouple the options implementation from the main
firmware in order to speed up development of new features, and decrease the 
number of potetional bugs in the main firmware.

_Vad är det som examensarbetet ska leda till?_

##Problem

How is the options handled currently?
how are the options stored internaly, what data structures and are they applicable on the new module?
what type of hardware do we need to add, what are the requirements?


How will the CAN bus be affected if additional controllers is added as The 
company runs the bus in the slowest speed according to the CAN bus standard.

_Här ska de specifika frågeställningarna beskrivas_
_Det ska vara regelrätta frågor som avslutas med frågetecken_

##Delimitations
The time will not be sufficient to develop a full scale version of the options
handling. With respect to that, we have chosen to spend most of the time 
developing a working architecture, and a prototype. The prototype will be
written with flexibility in mind. This meaning it will be written in such way
that it should be easy to extend it with new features such as a graphical 
interface. From a testing perspective, this is the natural way to go.

The fundamental part of this thesis is the development of an architecture 
as general as possible. It is therefore not vital that we implement all the 
existing options, as long as the architecture can be deemed good enough to 
handle them. Then we might choose a few options, preferalby some of the more 
vital, to implement for validation purposes.

Further, one possible delimitation might be to hand off the MCU side of the
development to The company. This option, however, depends on how much time 
The company can spare.
This delimitation is only applicable if we decide to put the options handling in
an external chip. In this case, all of the options currently existing shall be
implemented.

The communication between the MCU and the indented extra unit will occur over
the CAN bus. This means that the protocol must be implemented in the prototype.
The results will be validated with the help of a HIL (Hardware In the Loop) 
system and/or with a truck.


_Här beskrivs kortfattat de viktigaste avgränsningarna som medvetet gjorts._
_Det kan till exempel gälla att man fokuserat arbetet på en viss tilämpningsdomän_
_eller målgrupp_


#Background (optional)
Today, The company handles a big quantity of customer specific options
on their fork lifts. The options are all being built in into the main controller
(MCU) of the truck. This leads to problems:

 * Developing the options requires a lot of resources, this because it began as 
   a "one-off job".
 * Because all of the features exists in the main firmware, the code becomes
   very complex and hard to follow. Many of the features are also inactivated 
   for most of the customers.
 * The available code memory will soon be filled. Adding additional code will 
   require a larger on chip memory.

The company is looking for an options handling solution which allows the 
functionality to be moved from the MCU to a separate controller.

#Theory


#Method


#Result


#Discussion

##Result


##Method


#Conclusions


#References


