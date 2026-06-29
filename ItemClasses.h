#ifndef ITEMCLASSES_H
#define ITEMCLASSES_H

#include <string>
#include "SimpleDate.h"

using namespace std;

// Class 1: Base system entity
class SystemEntity {
private:
    int entityId;

public:
    SystemEntity();
    SystemEntity(int id);
    int getEntityId() const;
    void setEntityId(int id);
    virtual void displayDetails() const;
    virtual ~SystemEntity();
};

// CLASS 2: Core Item details (Inherits from SystemEntity)
class Item : public SystemEntity {
private:
    string itemName;
    string itemDescription;
    SimpleDate recordDate; // Composition (Object Relationship)

public:
    Item();
    Item(int id, string name, string desc, string dStr);
    string getItemName() const;
    void setItemName(string name);
    string getItemDescription() const;
    void setItemDescription(string desc);
    string getDate() const;
    void setDate(string dStr);
    void displayDetails() const override;
};

// CLASS 3: Adds Location & Status (Inherits from Item)
class ReportedItem : public Item {
private:
    string location;
    string status;

public:
    ReportedItem();
    ReportedItem(int id, string name, string desc, string dStr, string loc, string stat = "Active");
    string getLocation() const;
    void setLocation(string loc);
    string getStatus() const;
    void setStatus(string stat);
    void displayDetails() const override;
};

// CLASS 4: Final Lost Item class (Inherits from ReportedItem)
class LostItem : public ReportedItem {
private:
    string ownerName;
    string contactNumber;

public:
    LostItem();
    LostItem(int id, string name, string desc, string dStr, string loc, string owner, string contact, string stat = "Active");
    string getOwnerName() const;
    string getContactNumber() const;
    void displayDetails() const override;
};

// CLASS 5: Found Item class (Inherits from ReportedItem)
class FoundItem : public ReportedItem {
private:
    string finderName;
    string storageLocation;

public:
    FoundItem();
    FoundItem(int id, string name, string desc, string dStr, string loc, string finder, string storage, string stat = "Active");
    string getFinderName() const;
    string getStorageLocation() const;
    void displayDetails() const override;
};

#endif