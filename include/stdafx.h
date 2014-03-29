#ifndef STDAFX_H
#define STDAFX_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <tr1/memory>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <TGUI/TGUI.hpp>

#include <Box2D/Box2D.h>

#define PI 3.1415926

#endif//STFAFX_H

/** Coding Nomenclature and Standard Practices

///help do we use protected or private for inheritance?
INCLUDING:
Always have an include guard.
Never include .cpp files!
use #include "filename" for files we created
use #include <filename> for files we didn't create
#define constants go in stdafx.h

COMMENTING:
If you are creating, dereferencing, or otherwise interacting with pointers, put //pointer; right after it, plus anything else that needs to be described
If there is something that needs to be created in the future, put ///code here
If you are writing something for the purpose of debugging, put //debug after it!
The term smart* means smart pointer.

GENERAL STUFF:
Only make functions virtual if you actually plan to override them.
Only make stuff protected if the class will actually have a child.
Always inherit publicly.
Never use any namespaces in header files.
Always do using namespace std; in cpp files, and namespace sf if there is a lot of sf stuff.
Comment things that aren't obvious, but don't comment things that are obvious, like getVariableName and setVariableName
Most objects should have a constructor that creates a really generic version of itself with some properties for testing
When creating pointers and references, put the * and & next to the var type, because that symbol changes the variable type, so int* pExampleInt;
Pass stuff around by value if its an individual STL data type, like in or string, const reference when its more complex data
Use pointers if the lifetime of an object is not known.
Use const when possible


POINTERS:
Things that cause pointers to go wrong are:
Objects getting destroyed when you think they aren't going to be.
Vectors
Any STL containers for that matter.
If you're writing code that dereferences any pointer, test it frequently and rigorously.
Put a comment of //pointer next to any pointer dereference.


SFML:
Use Vector2f when possible in sfml.
Sprites hold a reference to a texture, so the texture needs to not get destroyed.
Textures are heavy, Sprites are light.


NOMENCLATURE:
http://stackoverflow.com/questions/1866794/naming-classes-how-to-avoid-calling-everything-a-whatevermanager
The first letter of every word in class names are always capitalized like GameManager, or ActiveEventer
The first letter of the first word in any instance of any type is lower case. So GameManager gameManager; or int craigFritz;
Function names follow the rules of instances.
Make the first letter Capital for lists
Vectors of a TYPE should be named BlahBlahList, so vector<CottonCandy> m_CottonCandyList;
If its a vector of pointers or smart pointers, do m_CottonCandySPList or m_CottonCandyPList where appropriate
notice the capital letters!!

Prefixes of variables and or functions are as follows, and
append the Prefix in the order of top to bottom:


ABREVIATIONS:
position    pos
texture(d)(s)     tex
coordinates coords
pixels      pix
conversion  conv
vertices    vert


PREFIX: SITUATION:              EXAMPLE:
f_  private member function     f_link();
s_  private member struct var   s_health;
m_  private member variable     m_yourMom;
r   variable is a reference     rYourMom;
p   variable is a pointer       pBadBear;
sp  variable is a smart ptr     spBadBear;
it_ variable is an iterator     it_data; //if its the only iterator in the loop, just use "it" for the name

multiple: m_pVar, m_rVar

**/
