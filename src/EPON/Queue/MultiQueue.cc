//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "MultiQueue.h"

Define_Module(MultiQueue);

MultiQueue::MultiQueue() {

}

MultiQueue::~MultiQueue() {
    for(int i = 0;i < intpar("numONUs");i++) delete queue[i];
}

void MultiQueue::initialize() {
    for (int i = 0;i < intpar("numONUs");i++)
    {
        Queue* q = new Queue();
        q->initialize();
        queue.push_back(q);
        setPopForwarded(i,false);
    }
}

//report
void MultiQueue::setNonStrict(int LLID,bool NonStrict) {
    queue[LLID]->setNonStrict(NonStrict);
}

void MultiQueue::setPopForwarded(int LLID,bool b) {
    queue[LLID]->setPopForwarded(b);
}

void MultiQueue::forward(int LLID,int priority) {
    queue[LLID]->forward(priority);
}

int MultiQueue::getForwardLength(int LLID) {
    return queue[LLID]->getForwardLength();
}

int MultiQueue::getForwardLength(int LLID,int priority) {
    return queue[LLID]->getForwardLength(priority);
}

int MultiQueue::getForwardSize(int LLID) {
    return queue[LLID]->getForwardSize();
}

int MultiQueue::getForwardSize(int LLID,int priority) {
    return queue[LLID]->getForwardSize(priority);
}

//insertion and removal functions
void MultiQueue::insert(cPacket *packet) {
    DataFrame* data = check_and_cast<DataFrame*>(packet);
    int des = data->getDST();
    std::cout << " queue " << des - intpar("LLID_BASE") << "\n";
    queue[des - intpar("LLID_BASE")]->insert(data);
}

cPacket* MultiQueue::remove(cPacket *packet) {
    for(int i = 0; i < int(queue.size()); i++) {
        cPacket* p = queue.at(i)->remove(packet);
        if(p != NULL) return p;
    }
    return NULL;
}

cPacket* MultiQueue::pop() {
    if(front() != NULL)
    {
        DataFrame* data = check_and_cast<DataFrame*>(front());
        return queue.at(data->getDST())->pop();
    }
    return NULL;
}

cPacket* MultiQueue::pop(int LLID) {
    if(LLID >= 0 && LLID < intpar("numONUs")) return queue[LLID]->pop();
    throw cRuntimeError("[%s::pop] LLID out of bound ,LLID=", LLID);
}

//query functions
bool MultiQueue::isEmpty(int LLID) {
    return queue[LLID]->isEmpty();
}

bool MultiQueue::isEmpty() {
    for(int i = 0; i < int(queue.size()); i++)
        if(!queue.at(i)->isEmpty()) return false;
    return true;
}

bool MultiQueue::isEmptyByPriority(int LLID,int priority) {
    return queue[LLID]->isEmptyByPriority(priority);
}

int MultiQueue::getLength() {
    int sum = 0;
    for(int i = 0;i < int(queue.size());i++) sum += queue.at(i)->getLength();
    return sum;
}

int MultiQueue::getLength(int LLID) {
    return queue[LLID]->getLength();
}

int MultiQueue::getLengthByPriority(int LLID,int priority) {
    return queue[LLID]->getLengthByPriority(priority);
}

int64_t MultiQueue::getBitLength() {
    int64_t sum = 0;
    for(int i = 0; i < int(queue.size()); i++) sum += queue.at(i)->getBitLength();
    return sum;
}

int64_t MultiQueue::getBitLength(int LLID) {
    return queue[LLID]->getBitLength();
}

int64_t MultiQueue::getBitLengthByPriority(int LLID,int priority) {
    return queue[LLID]->getBitLengthByPriority(priority);
}

cPacket* MultiQueue::front() {
    simtime_t t = simTime();
    int LLID = -1;
    for(int i = 0; i < int(queue.size()); i++)
        if(front(i) != NULL)
        {
            DataFrame* data = check_and_cast<DataFrame*>(front(i));
            if (data->getRxTime() < t)
                t = data->getRxTime();
            LLID = i;
        }
    if(LLID == -1) return NULL;
    else return front(LLID);
}

cPacket* MultiQueue::front(int LLID) {
    return queue[LLID]->front();
}

cPacket* MultiQueue::back(int LLID) {
    return queue[LLID]->back();
}

