// Copyright (C) 2013-2014 Thalmic Labs Inc.
// Distributed under the Myo SDK license agreement. See LICENSE.txt for details.
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <unistd.h>
// The only file that needs to be included to use the Myo C++ SDK is myo.hpp.
#include <myo/myo.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <math.h>
#include <float.h>
struct node
{
    char ch;
    node *left,
    *right;
};
node *headNode;
node *currentNode;
float leftlimit = 1;
float rightlimit = 1;
float toplimit = 2;
float bottomlimit = 2;
// bigger number --> slower
int INIT_SPEED = 100;
int timeVal = INIT_SPEED;
//current position values
float rest_horizontal = 0;
float rest_vertical = 0;
std::string current_sentence = "";
std::string current_word = "";
int last_direction = -1;


node* goBack(node *tempNode, node *currentNode)
{
    if (tempNode == NULL)
    {
        return NULL;
    }
    else if (tempNode->left == currentNode || tempNode->right == currentNode)
    {
        return tempNode;
    }
    else if (goBack(tempNode->left, currentNode) != NULL)
    {
        return goBack(tempNode->left, currentNode);
    }
    else
    {
        return goBack(tempNode->right, currentNode);
    }
}
void createTree()
{
    //init tree
    headNode = new node();
    headNode->ch = '_'; //change to space later *****************************************************************
    headNode->left = new node();
    headNode->right = new node();
    currentNode = headNode;
    node *tNode = headNode->left;
    node *eNode = headNode->right;
    tNode->ch = 'T';
    eNode->ch = 'E';
    tNode->left = new node();
    tNode->right = new node();
    eNode->left = new node();
    eNode->right = new node();
    node *mNode = tNode->left;
    node *nNode = tNode->right;
    node *aNode = eNode->left;
    node *iNode = eNode->right;
    mNode->ch = 'M';
    nNode->ch = 'N';
    aNode->ch = 'A';
    iNode->ch = 'I';
    mNode->left = new node();
    mNode->right = new node();
    nNode->left = new node();
    nNode->right = new node();
    aNode->left = new node();
    aNode->right = new node();
    iNode->left = new node();
    iNode->right = new node();
    node *oNode = mNode->left;
    node *gNode = mNode->right;
    node *kNode = nNode->left;
    node *dNode = nNode->right;
    node *wNode = aNode->left;
    node *rNode = aNode->right;
    node *uNode = iNode->left;
    node *sNode = iNode->right;
    oNode->ch = 'O';
    gNode->ch = 'G';
    kNode->ch = 'K';
    dNode->ch = 'D';
    wNode->ch = 'W';
    rNode->ch = 'R';
    uNode->ch = 'U';
    sNode->ch = 'S';
    oNode->left = new node();
    oNode->right = new node();
    gNode->left = new node();
    gNode->right = new node();
    kNode->left = new node();
    kNode->right = new node();
    dNode->left = new node();
    dNode->right = new node();
    wNode->left = new node();
    wNode->right = new node();
    rNode->left = new node();
    rNode->right = new node();
    uNode->left = new node();
    uNode->right = new node();
    sNode->left = new node();
    sNode->right = new node();
    node *commaNode = oNode->left;
    node *periodNode = oNode->right;
    node *qNode = gNode->left;
    node *zNode = gNode->right;
    node *yNode = kNode->left;
    node *cNode = kNode->right;
    node *xNode = dNode->left;
    node *bNode = dNode->right;
    node *jNode = wNode->left;
    node *pNode = wNode->right;
    node *slashNode = rNode->left;
    node *lNode = rNode->right;
    node *hyphenNode = uNode->left;
    node *fNode = uNode->right;
    node *vNode = sNode->left;
    node *hNode = sNode->right;
    commaNode->ch = ',';
    periodNode->ch = '.';
    qNode->ch = 'Q';
    zNode->ch = 'Z';
    yNode->ch = 'Y';
    cNode->ch = 'C';
    xNode->ch = 'X';
    bNode->ch = 'B';
    jNode->ch = 'J';
    pNode->ch = 'P';
    slashNode->ch = '/';
    lNode->ch = 'L';
    hyphenNode->ch = '-';
    fNode->ch = 'F';
    vNode->ch = 'V';
    hNode->ch = 'H';
    commaNode->left = new node();
    commaNode->right = new node();
    periodNode->right = new node();
    zNode->right = new node();
    bNode->right = new node();
    jNode->left = new node();
    hyphenNode->left = new node();
    vNode->left = new node();
    hNode->left = new node();
    hNode->right = new node();
    node *zeroNode = commaNode->left;
    node *nineNode = commaNode->right;
    node *eightNode = periodNode->right;
    node *sevenNode = zNode->right;
    node *sixNode = bNode->right;
    node *oneNode = jNode->left;
    node *twoNode = hyphenNode->left;
    node *threeNode = vNode->left;
    node *fourNode = hNode->left;
    node *fiveNode = hNode->right;
    zeroNode->ch = '0';
    oneNode->ch = '1';
    twoNode->ch = '2';
    threeNode->ch = '3';
    fourNode->ch = '4';
    fiveNode->ch= '5';
    sixNode->ch = '6';
    sevenNode->ch = '7';
    eightNode->ch = '8';
    nineNode->ch = '9';
}

void selectChar()
{
    current_word = current_word + currentNode->ch;
    currentNode = headNode;
    
}

void move(int direction)
{
    
    //move left (direction = 0)
    if (currentNode->left != NULL && direction == 0)
    {
        currentNode = currentNode->left;
    }
    //move right (direction = 1)
    else if (currentNode->right != NULL && direction == 1)
    {
        currentNode = currentNode->right;
    }
    //move back or up
    else if (direction == 2)
    {
        currentNode = headNode;
        
        if( last_direction == 2 && current_word.length() != 0)
        {
            current_word = current_word.substr(0, current_word.length() - 1 );
        }

    }
    //move down
    else if( direction == 3)
    {
        selectChar();
    }
    else
    {
        //do nothing
    }
    last_direction = direction;
}

void reset()
{
    current_sentence = current_sentence + " ";
    current_word = "";
    currentNode = headNode;
    last_direction = -1;
}
int counter = 0;

void doAction(float roll, float vertical, float horizontal)
{
    
    counter++;
    if( counter == std::max( 1, timeVal) )
    {
        //std::cout << "(" << horizontal << ", " << vertical << ")" << std::endl;
        
        //up -> back
        if (vertical > rest_vertical + toplimit)
        {
            //std::cout << "up" << std::endl;
            move(2);
        }
        //down -> select
        else if (vertical < rest_vertical - bottomlimit)
        {
            //std::cout << "down" << std::endl;
            if (last_direction == 3)
            {
                std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
                current_sentence = current_sentence + current_word;
                std::cout << "You completed the word: " << current_word << ". Your complete sentence is: " << current_sentence << std::endl;
                reset();
            }
            else
            {
                move(3);
                
            }
        }
        // rest
        else if (horizontal < rest_horizontal + rightlimit && horizontal > rest_horizontal - leftlimit){
            //std::cout << "rest" << std::endl;
            //do nothing; rest
            move(4);
        }
        
        //JUST DONT GO NEAR X = 0 or X= 18
        // right -> right
        else if (!(!(horizontal < rest_horizontal + rightlimit) && (!(horizontal < fabs(rest_horizontal + rightlimit - leftlimit - 9.5)))))
        {
            //std::cout << "right" << std::endl;
            move(1);
        }
        // left -> left
        else {
            //std::cout << "left" << std::endl;
            move(0);
        }
        

        //WANT TO ADD THIS?????????????????
        if( roll > 8)
        {
            last_direction = 5;
        }
        else if ( roll < 3 )
        {
            last_direction = 6;
        }
        
        if (last_direction == 0)
        {
                    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
            std::cout << "You moved left. You are currently on " << currentNode->ch << std::endl;
        }
        else if(last_direction == 1)
        {
                    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
            std::cout << "You moved right. You are currently on " << currentNode->ch << std::endl;
        }
        else if(last_direction == 4 )
        {
                    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
            std::cout << "You did not move. You are currently on " << currentNode->ch << std::endl;
        }
        else if(last_direction == 2 )
        {
                    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
            std::cout << "You have removed your last selected character. Your current word is " << current_word << std::endl;
        }
        else if(last_direction == 3)
        {
                    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
            std::cout << "You selected " << current_word.substr(current_word.length()-1) << ". Complete word: " << current_word << std::endl;
        }
        else if( last_direction == 5 )
        {
                    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
            if( timeVal - 20 >= 0 )timeVal = timeVal - 20;
            std::cout << "Speed is now " << INIT_SPEED - timeVal << " (max " << INIT_SPEED << ")" << std::endl;
            //ORRR
            //current_sentence = "";
            //std::cout << "STARTED OVER" << std::endl;
        }
        else if (last_direction == 6 )
        {
                    std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;std::cout << std::endl;
            if( timeVal + 20 <= INIT_SPEED ) timeVal = timeVal + 20;
             std::cout << "Speed is now " << INIT_SPEED - timeVal << " (min "  << 0 << ")" << std::endl;
        }
        counter = 0;
    }
}
void setlimits (float lLimit, float rLimit, float tLimit, float bLimit){
    leftlimit = lLimit;
    rightlimit = rLimit;
    toplimit = tLimit;
    bottomlimit = bLimit;
}
// Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
// provides several virtual functions for handling different kinds of events. If you do not override an event, the
// default behavior is to do nothing.
class DataCollector : public myo::DeviceListener {
public:
    DataCollector()
    : onArm(false), isUnlocked(false), roll_w(0), vertical_w(0), horizontal_w(0), currentPose()
    {
    }
    // onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
    
    // onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
    // as a unit quaternion.
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {
        using std::atan2;
        using std::asin;
        using std::sqrt;
        using std::max;
        using std::min;
        // Calculate Euler angles (roll, vertical, and horizontal) from the unit quaternion.
        float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                           1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
        float vertical = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
        float horizontal = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                                 1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
        // Convert the floating point angles in radians to a scale from 0 to 18.
        roll_w = static_cast<float>((roll + (float)M_PI) / (M_PI * 2.0f) * 18);
        vertical_w = static_cast<float>((vertical + (float)M_PI / 2.0f) / M_PI * 18);
        horizontal_w = static_cast<float>((horizontal + (float)M_PI) / (M_PI * 2.0f) * 18);
        
        
        doAction(roll_w, vertical_w, horizontal_w);
        //std::cout << currentNode->ch << std::endl;
    }
    // onPose() is called whenever the Myo detects that the person wearing it has changed their pose, for example,
    // making a fist, or not making a fist anymore.
    void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
    {
        currentPose = pose;
    }
    // onArmSync() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
    // arm. This lets Myo know which arm it's on and which way it's facing.
    void onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation,
                   myo::WarmupState warmupState)
    {
        onArm = true;
        whichArm = arm;
    }
    // onArmUnsync() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
    // it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
    // when Myo is moved around on the arm.
    void onArmUnsync(myo::Myo* myo, uint64_t timestamp)
    {
        onArm = false;
    }
    // onUnlock() is called whenever Myo has become unlocked, and will start delivering pose events.
    void onUnlock(myo::Myo* myo, uint64_t timestamp)
    {
        isUnlocked = true;
    }
    // onLock() is called whenever Myo has become locked. No pose events will be sent until the Myo is unlocked again.
    void onLock(myo::Myo* myo, uint64_t timestamp)
    {
        isUnlocked = false;
    }
    // There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
    // For this example, the functions overridden above are sufficient.
    // We define this function to print the current values that were updated by the on...() functions above.
    
    float getRoll()
    {
        return roll_w;
    }
    
    float getVertical()
    {
        return vertical_w;
    }
    
    float getHorizontal()
    {
        return horizontal_w;
    }
    
    // These values are set by onArmSync() and onArmUnsync() above.
    bool onArm;
    myo::Arm whichArm;
    // This is set by onUnlocked() and onLocked() above.
    bool isUnlocked;
    // These values are set by onOrientationData() and onPose() above.
    float roll_w, vertical_w, horizontal_w;
    myo::Pose currentPose;
    
};
int main(int argc, char** argv)
{
    float lLimit = 0.5;
    float rLimit = 0.5;
    float tLimit = 1.5;
    float bLimit = 1.5;
    
    std:: cout << "Get ready in REST position." << std::endl;
    
    sleep(1);
    
    createTree();
    
    myo::Hub hub("com.example.hello-myo");
    DataCollector collector;
    hub.addListener(&collector);
    
    hub.run(1000/20);
    
    rest_horizontal = collector.getHorizontal();
    rest_vertical = collector.getVertical();
    
    
    setlimits(lLimit, rLimit, tLimit, bLimit);
    
    //std::cout << "(" << rest_horizontal << ", " << rest_vertical << ")" << std::endl;
    // Finally we enter our main loop.
    while (1) {
        // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
        // In this case, we wish to update our display 20 times a second, so we run for 1000/20 milliseconds.
        hub.run(1000/20);
        // After processing events, we call the print() member function we defined above to print out the values we've
        // obtained from any events that have occurred.
        //collector.print();
        
    }
}
