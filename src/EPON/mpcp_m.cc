//
// Generated file, do not edit! Created by nedtool 5.0 from src/EPON/mpcp.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "mpcp_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("FrameTag");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("FrameTag"));
    e->insert(TagNormal, "TagNormal");
    e->insert(TagDebug, "TagDebug");
    e->insert(TagFront, "TagFront");
    e->insert(TagBack, "TagBack");
    e->insert(TagFrontAndBack, "TagFrontAndBack");
);

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("Response");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("Response"));
    e->insert(NOSIGNAL, "NOSIGNAL");
    e->insert(NONE, "NONE");
    e->insert(ACK, "ACK");
    e->insert(NACK, "NACK");
    e->insert(CS, "CS");
    e->insert(DS, "DS");
);

Register_Class(Frame);

Frame::Frame(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->DST = 0;
    this->SRC = 0;
    this->rxTime = 0;
    this->txTime = 0;
    this->tag = TagNormal;
}

Frame::Frame(const Frame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Frame::~Frame()
{
}

Frame& Frame::operator=(const Frame& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Frame::copy(const Frame& other)
{
    this->DST = other.DST;
    this->SRC = other.SRC;
    this->rxTime = other.rxTime;
    this->txTime = other.txTime;
    this->tag = other.tag;
}

void Frame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->DST);
    doParsimPacking(b,this->SRC);
    doParsimPacking(b,this->rxTime);
    doParsimPacking(b,this->txTime);
    doParsimPacking(b,this->tag);
}

void Frame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->DST);
    doParsimUnpacking(b,this->SRC);
    doParsimUnpacking(b,this->rxTime);
    doParsimUnpacking(b,this->txTime);
    doParsimUnpacking(b,this->tag);
}

int64_t Frame::getDST() const
{
    return this->DST;
}

void Frame::setDST(int64_t DST)
{
    this->DST = DST;
}

int64_t Frame::getSRC() const
{
    return this->SRC;
}

void Frame::setSRC(int64_t SRC)
{
    this->SRC = SRC;
}

::omnetpp::simtime_t Frame::getRxTime() const
{
    return this->rxTime;
}

void Frame::setRxTime(::omnetpp::simtime_t rxTime)
{
    this->rxTime = rxTime;
}

::omnetpp::simtime_t Frame::getTxTime() const
{
    return this->txTime;
}

void Frame::setTxTime(::omnetpp::simtime_t txTime)
{
    this->txTime = txTime;
}

int Frame::getTag() const
{
    return this->tag;
}

void Frame::setTag(int tag)
{
    this->tag = tag;
}

class FrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    FrameDescriptor();
    virtual ~FrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FrameDescriptor);

FrameDescriptor::FrameDescriptor() : omnetpp::cClassDescriptor("Frame", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

FrameDescriptor::~FrameDescriptor()
{
    delete[] propertynames;
}

bool FrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Frame *>(obj)!=nullptr;
}

const char **FrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int FrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *FrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "DST",
        "SRC",
        "rxTime",
        "txTime",
        "tag",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int FrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DST")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SRC")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "rxTime")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "txTime")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "tag")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int64_t",
        "int64_t",
        "simtime_t",
        "simtime_t",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **FrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 4: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *FrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 4:
            if (!strcmp(propertyname,"enum")) return "FrameTag";
            return nullptr;
        default: return nullptr;
    }
}

int FrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        case 0: return int642string(pp->getDST());
        case 1: return int642string(pp->getSRC());
        case 2: return simtime2string(pp->getRxTime());
        case 3: return simtime2string(pp->getTxTime());
        case 4: return enum2string(pp->getTag(), "FrameTag");
        default: return "";
    }
}

bool FrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        case 0: pp->setDST(string2int64(value)); return true;
        case 1: pp->setSRC(string2int64(value)); return true;
        case 2: pp->setRxTime(string2simtime(value)); return true;
        case 3: pp->setTxTime(string2simtime(value)); return true;
        case 4: pp->setTag((FrameTag)string2enum(value, "FrameTag")); return true;
        default: return false;
    }
}

const char *FrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(DataFrame);

DataFrame::DataFrame(const char *name, int kind) : ::Frame(name,kind)
{
    this->vacation = false;
    this->residualTime = 0;
    this->queueTime = 0;
    this->forwarded = false;
    this->s1Delay = 0;
    this->burstTime = 0;
}

DataFrame::DataFrame(const DataFrame& other) : ::Frame(other)
{
    copy(other);
}

DataFrame::~DataFrame()
{
}

DataFrame& DataFrame::operator=(const DataFrame& other)
{
    if (this==&other) return *this;
    ::Frame::operator=(other);
    copy(other);
    return *this;
}

void DataFrame::copy(const DataFrame& other)
{
    this->vacation = other.vacation;
    this->residualTime = other.residualTime;
    this->queueTime = other.queueTime;
    this->forwarded = other.forwarded;
    this->s1Delay = other.s1Delay;
    this->burstTime = other.burstTime;
}

void DataFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::Frame::parsimPack(b);
    doParsimPacking(b,this->vacation);
    doParsimPacking(b,this->residualTime);
    doParsimPacking(b,this->queueTime);
    doParsimPacking(b,this->forwarded);
    doParsimPacking(b,this->s1Delay);
    doParsimPacking(b,this->burstTime);
}

void DataFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::Frame::parsimUnpack(b);
    doParsimUnpacking(b,this->vacation);
    doParsimUnpacking(b,this->residualTime);
    doParsimUnpacking(b,this->queueTime);
    doParsimUnpacking(b,this->forwarded);
    doParsimUnpacking(b,this->s1Delay);
    doParsimUnpacking(b,this->burstTime);
}

bool DataFrame::getVacation() const
{
    return this->vacation;
}

void DataFrame::setVacation(bool vacation)
{
    this->vacation = vacation;
}

::omnetpp::simtime_t DataFrame::getResidualTime() const
{
    return this->residualTime;
}

void DataFrame::setResidualTime(::omnetpp::simtime_t residualTime)
{
    this->residualTime = residualTime;
}

::omnetpp::simtime_t DataFrame::getQueueTime() const
{
    return this->queueTime;
}

void DataFrame::setQueueTime(::omnetpp::simtime_t queueTime)
{
    this->queueTime = queueTime;
}

bool DataFrame::getForwarded() const
{
    return this->forwarded;
}

void DataFrame::setForwarded(bool forwarded)
{
    this->forwarded = forwarded;
}

::omnetpp::simtime_t DataFrame::getS1Delay() const
{
    return this->s1Delay;
}

void DataFrame::setS1Delay(::omnetpp::simtime_t s1Delay)
{
    this->s1Delay = s1Delay;
}

::omnetpp::simtime_t DataFrame::getBurstTime() const
{
    return this->burstTime;
}

void DataFrame::setBurstTime(::omnetpp::simtime_t burstTime)
{
    this->burstTime = burstTime;
}

class DataFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    DataFrameDescriptor();
    virtual ~DataFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(DataFrameDescriptor);

DataFrameDescriptor::DataFrameDescriptor() : omnetpp::cClassDescriptor("DataFrame", "Frame")
{
    propertynames = nullptr;
}

DataFrameDescriptor::~DataFrameDescriptor()
{
    delete[] propertynames;
}

bool DataFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DataFrame *>(obj)!=nullptr;
}

const char **DataFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *DataFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int DataFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int DataFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *DataFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vacation",
        "residualTime",
        "queueTime",
        "forwarded",
        "s1Delay",
        "burstTime",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int DataFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "vacation")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "residualTime")==0) return base+1;
    if (fieldName[0]=='q' && strcmp(fieldName, "queueTime")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "forwarded")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "s1Delay")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "burstTime")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *DataFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "simtime_t",
        "simtime_t",
        "bool",
        "simtime_t",
        "simtime_t",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **DataFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DataFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DataFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    DataFrame *pp = (DataFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DataFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    DataFrame *pp = (DataFrame *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getVacation());
        case 1: return simtime2string(pp->getResidualTime());
        case 2: return simtime2string(pp->getQueueTime());
        case 3: return bool2string(pp->getForwarded());
        case 4: return simtime2string(pp->getS1Delay());
        case 5: return simtime2string(pp->getBurstTime());
        default: return "";
    }
}

bool DataFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    DataFrame *pp = (DataFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setVacation(string2bool(value)); return true;
        case 1: pp->setResidualTime(string2simtime(value)); return true;
        case 2: pp->setQueueTime(string2simtime(value)); return true;
        case 3: pp->setForwarded(string2bool(value)); return true;
        case 4: pp->setS1Delay(string2simtime(value)); return true;
        case 5: pp->setBurstTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *DataFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *DataFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    DataFrame *pp = (DataFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(MPCPGate);

MPCPGate::MPCPGate(const char *name, int kind) : ::Frame(name,kind)
{
    this->startTime = 0;
    this->length = 0;
}

MPCPGate::MPCPGate(const MPCPGate& other) : ::Frame(other)
{
    copy(other);
}

MPCPGate::~MPCPGate()
{
}

MPCPGate& MPCPGate::operator=(const MPCPGate& other)
{
    if (this==&other) return *this;
    ::Frame::operator=(other);
    copy(other);
    return *this;
}

void MPCPGate::copy(const MPCPGate& other)
{
    this->startTime = other.startTime;
    this->length = other.length;
}

void MPCPGate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::Frame::parsimPack(b);
    doParsimPacking(b,this->startTime);
    doParsimPacking(b,this->length);
}

void MPCPGate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::Frame::parsimUnpack(b);
    doParsimUnpacking(b,this->startTime);
    doParsimUnpacking(b,this->length);
}

::omnetpp::simtime_t MPCPGate::getStartTime() const
{
    return this->startTime;
}

void MPCPGate::setStartTime(::omnetpp::simtime_t startTime)
{
    this->startTime = startTime;
}

::omnetpp::simtime_t MPCPGate::getLength() const
{
    return this->length;
}

void MPCPGate::setLength(::omnetpp::simtime_t length)
{
    this->length = length;
}

class MPCPGateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MPCPGateDescriptor();
    virtual ~MPCPGateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(MPCPGateDescriptor);

MPCPGateDescriptor::MPCPGateDescriptor() : omnetpp::cClassDescriptor("MPCPGate", "Frame")
{
    propertynames = nullptr;
}

MPCPGateDescriptor::~MPCPGateDescriptor()
{
    delete[] propertynames;
}

bool MPCPGateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MPCPGate *>(obj)!=nullptr;
}

const char **MPCPGateDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MPCPGateDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MPCPGateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int MPCPGateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *MPCPGateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "startTime",
        "length",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int MPCPGateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "startTime")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MPCPGateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
        "simtime_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **MPCPGateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MPCPGateDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MPCPGateDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MPCPGate *pp = (MPCPGate *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MPCPGateDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MPCPGate *pp = (MPCPGate *)object; (void)pp;
    switch (field) {
        case 0: return simtime2string(pp->getStartTime());
        case 1: return simtime2string(pp->getLength());
        default: return "";
    }
}

bool MPCPGateDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MPCPGate *pp = (MPCPGate *)object; (void)pp;
    switch (field) {
        case 0: pp->setStartTime(string2simtime(value)); return true;
        case 1: pp->setLength(string2simtime(value)); return true;
        default: return false;
    }
}

const char *MPCPGateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *MPCPGateDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MPCPGate *pp = (MPCPGate *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(MPCPReport);

MPCPReport::MPCPReport(const char *name, int kind) : ::Frame(name,kind)
{
    this->requiredBandwidth = 0;
    this->startTime = 0;
}

MPCPReport::MPCPReport(const MPCPReport& other) : ::Frame(other)
{
    copy(other);
}

MPCPReport::~MPCPReport()
{
}

MPCPReport& MPCPReport::operator=(const MPCPReport& other)
{
    if (this==&other) return *this;
    ::Frame::operator=(other);
    copy(other);
    return *this;
}

void MPCPReport::copy(const MPCPReport& other)
{
    this->requiredBandwidth = other.requiredBandwidth;
    this->startTime = other.startTime;
}

void MPCPReport::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::Frame::parsimPack(b);
    doParsimPacking(b,this->requiredBandwidth);
    doParsimPacking(b,this->startTime);
}

void MPCPReport::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::Frame::parsimUnpack(b);
    doParsimUnpacking(b,this->requiredBandwidth);
    doParsimUnpacking(b,this->startTime);
}

int MPCPReport::getRequiredBandwidth() const
{
    return this->requiredBandwidth;
}

void MPCPReport::setRequiredBandwidth(int requiredBandwidth)
{
    this->requiredBandwidth = requiredBandwidth;
}

::omnetpp::simtime_t MPCPReport::getStartTime() const
{
    return this->startTime;
}

void MPCPReport::setStartTime(::omnetpp::simtime_t startTime)
{
    this->startTime = startTime;
}

class MPCPReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MPCPReportDescriptor();
    virtual ~MPCPReportDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(MPCPReportDescriptor);

MPCPReportDescriptor::MPCPReportDescriptor() : omnetpp::cClassDescriptor("MPCPReport", "Frame")
{
    propertynames = nullptr;
}

MPCPReportDescriptor::~MPCPReportDescriptor()
{
    delete[] propertynames;
}

bool MPCPReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MPCPReport *>(obj)!=nullptr;
}

const char **MPCPReportDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MPCPReportDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MPCPReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int MPCPReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *MPCPReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requiredBandwidth",
        "startTime",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int MPCPReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requiredBandwidth")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "startTime")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MPCPReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "simtime_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **MPCPReportDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MPCPReportDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MPCPReportDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MPCPReport *pp = (MPCPReport *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MPCPReportDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MPCPReport *pp = (MPCPReport *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRequiredBandwidth());
        case 1: return simtime2string(pp->getStartTime());
        default: return "";
    }
}

bool MPCPReportDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MPCPReport *pp = (MPCPReport *)object; (void)pp;
    switch (field) {
        case 0: pp->setRequiredBandwidth(string2long(value)); return true;
        case 1: pp->setStartTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *MPCPReportDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *MPCPReportDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MPCPReport *pp = (MPCPReport *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(SLAGate);

SLAGate::SLAGate(const char *name, int kind) : ::MPCPGate(name,kind)
{
    this->signal = 0;
    this->sleepTime = 0;
    this->wakeUpTime = 0;
}

SLAGate::SLAGate(const SLAGate& other) : ::MPCPGate(other)
{
    copy(other);
}

SLAGate::~SLAGate()
{
}

SLAGate& SLAGate::operator=(const SLAGate& other)
{
    if (this==&other) return *this;
    ::MPCPGate::operator=(other);
    copy(other);
    return *this;
}

void SLAGate::copy(const SLAGate& other)
{
    this->signal = other.signal;
    this->sleepTime = other.sleepTime;
    this->wakeUpTime = other.wakeUpTime;
}

void SLAGate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::MPCPGate::parsimPack(b);
    doParsimPacking(b,this->signal);
    doParsimPacking(b,this->sleepTime);
    doParsimPacking(b,this->wakeUpTime);
}

void SLAGate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::MPCPGate::parsimUnpack(b);
    doParsimUnpacking(b,this->signal);
    doParsimUnpacking(b,this->sleepTime);
    doParsimUnpacking(b,this->wakeUpTime);
}

int SLAGate::getSignal() const
{
    return this->signal;
}

void SLAGate::setSignal(int signal)
{
    this->signal = signal;
}

::omnetpp::simtime_t SLAGate::getSleepTime() const
{
    return this->sleepTime;
}

void SLAGate::setSleepTime(::omnetpp::simtime_t sleepTime)
{
    this->sleepTime = sleepTime;
}

::omnetpp::simtime_t SLAGate::getWakeUpTime() const
{
    return this->wakeUpTime;
}

void SLAGate::setWakeUpTime(::omnetpp::simtime_t wakeUpTime)
{
    this->wakeUpTime = wakeUpTime;
}

class SLAGateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SLAGateDescriptor();
    virtual ~SLAGateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(SLAGateDescriptor);

SLAGateDescriptor::SLAGateDescriptor() : omnetpp::cClassDescriptor("SLAGate", "MPCPGate")
{
    propertynames = nullptr;
}

SLAGateDescriptor::~SLAGateDescriptor()
{
    delete[] propertynames;
}

bool SLAGateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SLAGate *>(obj)!=nullptr;
}

const char **SLAGateDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SLAGateDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SLAGateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int SLAGateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *SLAGateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "signal",
        "sleepTime",
        "wakeUpTime",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int SLAGateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "signal")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sleepTime")==0) return base+1;
    if (fieldName[0]=='w' && strcmp(fieldName, "wakeUpTime")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SLAGateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "simtime_t",
        "simtime_t",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **SLAGateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *SLAGateDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "Response";
            return nullptr;
        default: return nullptr;
    }
}

int SLAGateDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SLAGate *pp = (SLAGate *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SLAGateDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SLAGate *pp = (SLAGate *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getSignal(), "Response");
        case 1: return simtime2string(pp->getSleepTime());
        case 2: return simtime2string(pp->getWakeUpTime());
        default: return "";
    }
}

bool SLAGateDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SLAGate *pp = (SLAGate *)object; (void)pp;
    switch (field) {
        case 0: pp->setSignal((Response)string2enum(value, "Response")); return true;
        case 1: pp->setSleepTime(string2simtime(value)); return true;
        case 2: pp->setWakeUpTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *SLAGateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *SLAGateDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SLAGate *pp = (SLAGate *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(SLAReport);

SLAReport::SLAReport(const char *name, int kind) : ::MPCPReport(name,kind)
{
    this->signal = 0;
}

SLAReport::SLAReport(const SLAReport& other) : ::MPCPReport(other)
{
    copy(other);
}

SLAReport::~SLAReport()
{
}

SLAReport& SLAReport::operator=(const SLAReport& other)
{
    if (this==&other) return *this;
    ::MPCPReport::operator=(other);
    copy(other);
    return *this;
}

void SLAReport::copy(const SLAReport& other)
{
    this->signal = other.signal;
}

void SLAReport::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::MPCPReport::parsimPack(b);
    doParsimPacking(b,this->signal);
}

void SLAReport::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::MPCPReport::parsimUnpack(b);
    doParsimUnpacking(b,this->signal);
}

int SLAReport::getSignal() const
{
    return this->signal;
}

void SLAReport::setSignal(int signal)
{
    this->signal = signal;
}

class SLAReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    SLAReportDescriptor();
    virtual ~SLAReportDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(SLAReportDescriptor);

SLAReportDescriptor::SLAReportDescriptor() : omnetpp::cClassDescriptor("SLAReport", "MPCPReport")
{
    propertynames = nullptr;
}

SLAReportDescriptor::~SLAReportDescriptor()
{
    delete[] propertynames;
}

bool SLAReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SLAReport *>(obj)!=nullptr;
}

const char **SLAReportDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *SLAReportDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int SLAReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int SLAReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *SLAReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "signal",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int SLAReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "signal")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *SLAReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **SLAReportDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *SLAReportDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "Response";
            return nullptr;
        default: return nullptr;
    }
}

int SLAReportDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    SLAReport *pp = (SLAReport *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SLAReportDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    SLAReport *pp = (SLAReport *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getSignal(), "Response");
        default: return "";
    }
}

bool SLAReportDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    SLAReport *pp = (SLAReport *)object; (void)pp;
    switch (field) {
        case 0: pp->setSignal((Response)string2enum(value, "Response")); return true;
        default: return false;
    }
}

const char *SLAReportDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *SLAReportDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    SLAReport *pp = (SLAReport *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(CSLAGate);

CSLAGate::CSLAGate(const char *name, int kind) : ::Frame(name,kind)
{
    this->Grant1TransceiverMode = 0;
    this->Grant1StartTime = 0;
    this->Grant1Length = 0;
    this->Grant2StartTime = 0;
    this->Grant2Length = 0;
}

CSLAGate::CSLAGate(const CSLAGate& other) : ::Frame(other)
{
    copy(other);
}

CSLAGate::~CSLAGate()
{
}

CSLAGate& CSLAGate::operator=(const CSLAGate& other)
{
    if (this==&other) return *this;
    ::Frame::operator=(other);
    copy(other);
    return *this;
}

void CSLAGate::copy(const CSLAGate& other)
{
    this->Grant1TransceiverMode = other.Grant1TransceiverMode;
    this->Grant1StartTime = other.Grant1StartTime;
    this->Grant1Length = other.Grant1Length;
    this->Grant2StartTime = other.Grant2StartTime;
    this->Grant2Length = other.Grant2Length;
}

void CSLAGate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::Frame::parsimPack(b);
    doParsimPacking(b,this->Grant1TransceiverMode);
    doParsimPacking(b,this->Grant1StartTime);
    doParsimPacking(b,this->Grant1Length);
    doParsimPacking(b,this->Grant2StartTime);
    doParsimPacking(b,this->Grant2Length);
}

void CSLAGate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::Frame::parsimUnpack(b);
    doParsimUnpacking(b,this->Grant1TransceiverMode);
    doParsimUnpacking(b,this->Grant1StartTime);
    doParsimUnpacking(b,this->Grant1Length);
    doParsimUnpacking(b,this->Grant2StartTime);
    doParsimUnpacking(b,this->Grant2Length);
}

int CSLAGate::getGrant1TransceiverMode() const
{
    return this->Grant1TransceiverMode;
}

void CSLAGate::setGrant1TransceiverMode(int Grant1TransceiverMode)
{
    this->Grant1TransceiverMode = Grant1TransceiverMode;
}

::omnetpp::simtime_t CSLAGate::getGrant1StartTime() const
{
    return this->Grant1StartTime;
}

void CSLAGate::setGrant1StartTime(::omnetpp::simtime_t Grant1StartTime)
{
    this->Grant1StartTime = Grant1StartTime;
}

::omnetpp::simtime_t CSLAGate::getGrant1Length() const
{
    return this->Grant1Length;
}

void CSLAGate::setGrant1Length(::omnetpp::simtime_t Grant1Length)
{
    this->Grant1Length = Grant1Length;
}

::omnetpp::simtime_t CSLAGate::getGrant2StartTime() const
{
    return this->Grant2StartTime;
}

void CSLAGate::setGrant2StartTime(::omnetpp::simtime_t Grant2StartTime)
{
    this->Grant2StartTime = Grant2StartTime;
}

::omnetpp::simtime_t CSLAGate::getGrant2Length() const
{
    return this->Grant2Length;
}

void CSLAGate::setGrant2Length(::omnetpp::simtime_t Grant2Length)
{
    this->Grant2Length = Grant2Length;
}

class CSLAGateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CSLAGateDescriptor();
    virtual ~CSLAGateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CSLAGateDescriptor);

CSLAGateDescriptor::CSLAGateDescriptor() : omnetpp::cClassDescriptor("CSLAGate", "Frame")
{
    propertynames = nullptr;
}

CSLAGateDescriptor::~CSLAGateDescriptor()
{
    delete[] propertynames;
}

bool CSLAGateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CSLAGate *>(obj)!=nullptr;
}

const char **CSLAGateDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CSLAGateDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CSLAGateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int CSLAGateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *CSLAGateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Grant1TransceiverMode",
        "Grant1StartTime",
        "Grant1Length",
        "Grant2StartTime",
        "Grant2Length",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int CSLAGateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='G' && strcmp(fieldName, "Grant1TransceiverMode")==0) return base+0;
    if (fieldName[0]=='G' && strcmp(fieldName, "Grant1StartTime")==0) return base+1;
    if (fieldName[0]=='G' && strcmp(fieldName, "Grant1Length")==0) return base+2;
    if (fieldName[0]=='G' && strcmp(fieldName, "Grant2StartTime")==0) return base+3;
    if (fieldName[0]=='G' && strcmp(fieldName, "Grant2Length")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CSLAGateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **CSLAGateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *CSLAGateDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "Response";
            return nullptr;
        default: return nullptr;
    }
}

int CSLAGateDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CSLAGate *pp = (CSLAGate *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CSLAGateDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CSLAGate *pp = (CSLAGate *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getGrant1TransceiverMode(), "Response");
        case 1: return simtime2string(pp->getGrant1StartTime());
        case 2: return simtime2string(pp->getGrant1Length());
        case 3: return simtime2string(pp->getGrant2StartTime());
        case 4: return simtime2string(pp->getGrant2Length());
        default: return "";
    }
}

bool CSLAGateDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CSLAGate *pp = (CSLAGate *)object; (void)pp;
    switch (field) {
        case 0: pp->setGrant1TransceiverMode((Response)string2enum(value, "Response")); return true;
        case 1: pp->setGrant1StartTime(string2simtime(value)); return true;
        case 2: pp->setGrant1Length(string2simtime(value)); return true;
        case 3: pp->setGrant2StartTime(string2simtime(value)); return true;
        case 4: pp->setGrant2Length(string2simtime(value)); return true;
        default: return false;
    }
}

const char *CSLAGateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *CSLAGateDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CSLAGate *pp = (CSLAGate *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(CSLAReport);

CSLAReport::CSLAReport(const char *name, int kind) : ::Frame(name,kind)
{
    this->Request1Length = 0;
}

CSLAReport::CSLAReport(const CSLAReport& other) : ::Frame(other)
{
    copy(other);
}

CSLAReport::~CSLAReport()
{
}

CSLAReport& CSLAReport::operator=(const CSLAReport& other)
{
    if (this==&other) return *this;
    ::Frame::operator=(other);
    copy(other);
    return *this;
}

void CSLAReport::copy(const CSLAReport& other)
{
    this->Request1Length = other.Request1Length;
}

void CSLAReport::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::Frame::parsimPack(b);
    doParsimPacking(b,this->Request1Length);
}

void CSLAReport::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::Frame::parsimUnpack(b);
    doParsimUnpacking(b,this->Request1Length);
}

int CSLAReport::getRequest1Length() const
{
    return this->Request1Length;
}

void CSLAReport::setRequest1Length(int Request1Length)
{
    this->Request1Length = Request1Length;
}

class CSLAReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CSLAReportDescriptor();
    virtual ~CSLAReportDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CSLAReportDescriptor);

CSLAReportDescriptor::CSLAReportDescriptor() : omnetpp::cClassDescriptor("CSLAReport", "Frame")
{
    propertynames = nullptr;
}

CSLAReportDescriptor::~CSLAReportDescriptor()
{
    delete[] propertynames;
}

bool CSLAReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CSLAReport *>(obj)!=nullptr;
}

const char **CSLAReportDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CSLAReportDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CSLAReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int CSLAReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CSLAReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Request1Length",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int CSLAReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "Request1Length")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CSLAReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **CSLAReportDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CSLAReportDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CSLAReportDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CSLAReport *pp = (CSLAReport *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CSLAReportDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CSLAReport *pp = (CSLAReport *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRequest1Length());
        default: return "";
    }
}

bool CSLAReportDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CSLAReport *pp = (CSLAReport *)object; (void)pp;
    switch (field) {
        case 0: pp->setRequest1Length(string2long(value)); return true;
        default: return false;
    }
}

const char *CSLAReportDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *CSLAReportDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CSLAReport *pp = (CSLAReport *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(GBAGate);

GBAGate::GBAGate(const char *name, int kind) : ::MPCPGate(name,kind)
{
    this->ONUSleepTime = 0;
}

GBAGate::GBAGate(const GBAGate& other) : ::MPCPGate(other)
{
    copy(other);
}

GBAGate::~GBAGate()
{
}

GBAGate& GBAGate::operator=(const GBAGate& other)
{
    if (this==&other) return *this;
    ::MPCPGate::operator=(other);
    copy(other);
    return *this;
}

void GBAGate::copy(const GBAGate& other)
{
    this->ONUSleepTime = other.ONUSleepTime;
}

void GBAGate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::MPCPGate::parsimPack(b);
    doParsimPacking(b,this->ONUSleepTime);
}

void GBAGate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::MPCPGate::parsimUnpack(b);
    doParsimUnpacking(b,this->ONUSleepTime);
}

::omnetpp::simtime_t GBAGate::getONUSleepTime() const
{
    return this->ONUSleepTime;
}

void GBAGate::setONUSleepTime(::omnetpp::simtime_t ONUSleepTime)
{
    this->ONUSleepTime = ONUSleepTime;
}

class GBAGateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GBAGateDescriptor();
    virtual ~GBAGateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GBAGateDescriptor);

GBAGateDescriptor::GBAGateDescriptor() : omnetpp::cClassDescriptor("GBAGate", "MPCPGate")
{
    propertynames = nullptr;
}

GBAGateDescriptor::~GBAGateDescriptor()
{
    delete[] propertynames;
}

bool GBAGateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GBAGate *>(obj)!=nullptr;
}

const char **GBAGateDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GBAGateDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GBAGateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int GBAGateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GBAGateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ONUSleepTime",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int GBAGateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='O' && strcmp(fieldName, "ONUSleepTime")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GBAGateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "simtime_t",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **GBAGateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GBAGateDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GBAGateDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GBAGate *pp = (GBAGate *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GBAGateDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GBAGate *pp = (GBAGate *)object; (void)pp;
    switch (field) {
        case 0: return simtime2string(pp->getONUSleepTime());
        default: return "";
    }
}

bool GBAGateDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GBAGate *pp = (GBAGate *)object; (void)pp;
    switch (field) {
        case 0: pp->setONUSleepTime(string2simtime(value)); return true;
        default: return false;
    }
}

const char *GBAGateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *GBAGateDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GBAGate *pp = (GBAGate *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(GBAReport);

GBAReport::GBAReport(const char *name, int kind) : ::MPCPReport(name,kind)
{
}

GBAReport::GBAReport(const GBAReport& other) : ::MPCPReport(other)
{
    copy(other);
}

GBAReport::~GBAReport()
{
}

GBAReport& GBAReport::operator=(const GBAReport& other)
{
    if (this==&other) return *this;
    ::MPCPReport::operator=(other);
    copy(other);
    return *this;
}

void GBAReport::copy(const GBAReport& other)
{
}

void GBAReport::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::MPCPReport::parsimPack(b);
}

void GBAReport::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::MPCPReport::parsimUnpack(b);
}

class GBAReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GBAReportDescriptor();
    virtual ~GBAReportDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GBAReportDescriptor);

GBAReportDescriptor::GBAReportDescriptor() : omnetpp::cClassDescriptor("GBAReport", "MPCPReport")
{
    propertynames = nullptr;
}

GBAReportDescriptor::~GBAReportDescriptor()
{
    delete[] propertynames;
}

bool GBAReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GBAReport *>(obj)!=nullptr;
}

const char **GBAReportDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GBAReportDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GBAReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int GBAReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *GBAReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int GBAReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GBAReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **GBAReportDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GBAReportDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GBAReportDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GBAReport *pp = (GBAReport *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GBAReportDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GBAReport *pp = (GBAReport *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool GBAReportDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GBAReport *pp = (GBAReport *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GBAReportDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *GBAReportDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GBAReport *pp = (GBAReport *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


