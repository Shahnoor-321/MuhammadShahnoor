#include "ItemClasses.h"
#include <iostream>
#include <iomanip>

using namespace std;

// --- SystemEntity ---
SystemEntity::SystemEntity() { entityId = 0; }
SystemEntity::SystemEntity(int id) { entityId = id; }
int SystemEntity::getEntityId() const { return entityId; }
void SystemEntity::setEntityId(int id) { entityId = id; }
void SystemEntity::displayDetails() const {
    cout << left << setw(18) << "ID:" << entityId << endl;
}
SystemEntity::~SystemEntity() {}

// --- Item ---
Item::Item() : SystemEntity() {
    itemName = "";
    itemDescription = "";
}
Item::Item(int id, string name, string desc, string dStr) : SystemEntity(id) {
    itemName = name;
    itemDescription = desc;
    recordDate.setDateFromString(dStr);
}
string Item::getItemName() const { return itemName; }
void Item::setItemName(string name) { itemName = name; }
string Item::getItemDescription() const { return itemDescription; }
void Item::setItemDescription(string desc) { itemDescription = desc; }
string Item::getDate() const { return recordDate.getDateString(); }
void Item::setDate(string dStr) { recordDate.setDateFromString(dStr); }
void Item::displayDetails() const {
    SystemEntity::displayDetails();
    cout << left << setw(18) << "Item Name:" << itemName << endl;
    cout << left << setw(18) << "Description:" << itemDescription << endl;
    cout << left << setw(18) << "Date Logged:" << recordDate.getDateString() << endl;
}

// --- ReportedItem ---
ReportedItem::ReportedItem() : Item() {
    location = "";
    status = "Active";
}
ReportedItem::ReportedItem(int id, string name, string desc, string dStr, string loc, string stat) 
    : Item(id, name, desc, dStr) {
    location = loc;
    status = stat;
}
string ReportedItem::getLocation() const { return location; }
void ReportedItem::setLocation(string loc) { location = loc; }
string ReportedItem::getStatus() const { return status; }
void ReportedItem::setStatus(string stat) { status = stat; }
void ReportedItem::displayDetails() const {
    Item::displayDetails();
    cout << left << setw(18) << "Location:" << location << endl;
    cout << left << setw(18) << "Status:" << status << endl;
}

// --- LostItem ---
LostItem::LostItem() : ReportedItem() {
    ownerName = "";
    contactNumber = "";
}
LostItem::LostItem(int id, string name, string desc, string dStr, string loc, string owner, string contact, string stat)
    : ReportedItem(id, name, desc, dStr, loc, stat) {
    ownerName = owner;
    contactNumber = contact;
}
string LostItem::getOwnerName() const { return ownerName; }
string LostItem::getContactNumber() const { return contactNumber; }
void LostItem::displayDetails() const {
    cout << "\n----------------------------------------\n";
    cout << " [LOST ITEM REPORT]\n";
    cout << "----------------------------------------\n";
    ReportedItem::displayDetails();
    cout << left << setw(18) << "Owner Name:" << ownerName << endl;
    cout << left << setw(18) << "Contact No:" << contactNumber << endl;
    cout << "----------------------------------------\n";
}

// --- FoundItem ---
FoundItem::FoundItem() : ReportedItem() {
    finderName = "";
    storageLocation = "";
}
FoundItem::FoundItem(int id, string name, string desc, string dStr, string loc, string finder, string storage, string stat)
    : ReportedItem(id, name, desc, dStr, loc, stat) {
    finderName = finder;
    storageLocation = storage;
}
string FoundItem::getFinderName() const { return finderName; }
string FoundItem::getStorageLocation() const { return storageLocation; }
void FoundItem::displayDetails() const {
    cout << "\n----------------------------------------\n";
    cout << " [FOUND ITEM REPORT]\n";
    cout << "----------------------------------------\n";
    ReportedItem::displayDetails();
    cout << left << setw(18) << "Finder Name:" << finderName << endl;
    cout << left << setw(18) << "Stored At:" << storageLocation << endl;
    cout << "----------------------------------------\n";
}