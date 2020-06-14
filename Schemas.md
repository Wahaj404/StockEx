# Database Schema

* Credentials
``` sql
CREATE TABLE Credentials (
    CNIC TEXT PRIMARY KEY NOT NULL,
    Password TEXT NOT NULL
);
```

* Account
``` sql
CREATE TABLE Accounts (
    CNIC TEXT PRIMARY KEY NOT NULL,
    Balance INT NOT NULL CHECK(Balance >= 0),
    FOREIGN KEY(CNIC) REFERENCES Credentials(CNIC)
);
```

* WatchList
``` sql
CREATE TABLE WatchLists (
    CNIC TEXT PRIMARY KEY NOT NULL,
    Companies TEXT NOT NULL,
    FOREIGN KEY(CNIC) REFERENCES Credentials(CNIC)
);
```

* Share
``` sql
CREATE TABLE Shares (
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    CNIC TEXT NOT NULL,
    Symbol TEXT NOT NULL,
    Buying_Price INT NOT NULL CHECK(Buying_Price > 0),
    FOREIGN KEY(CNIC) REFERENCES Credentials(CNIC),
    FOREIGN KEY(Symbol) REFERENCES Companies(Symbol)
);
```

* Company
``` sql
CREATE TABLE Companies (
    Symbol TEXT PRIMARY KEY NOT NULL,
    Current_Price INT NOT NULL CHECK(Current_Price > 0),
    Low INT NOT NULL CHECK(Low > 0),
    High INT NOT NULL CHECK(High > 0),
    Percent_Change REAL NOT NULL CHECK(Percent_Change <= 5.0 AND Percent_Change >= -5.0),
    Volume INT NOT NULL CHECK(Volume > 0)
);
```

* Listing
``` sql
CREATE TABLE Listings (
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    CNIC TEXT NOT NULL,
    Symbol TEXT NOT NULL,
    Price INT NOT NULL CHECK(Price > 0),
    Lot_Count INT NOT NULL CHECK(Lot_Count > 0),
    Listing_Type INT NOT NULL CHECK(Listing_Type == 0 OR Listing_Type == 1),
    Share_IDs TEXT NOT NULL,
    FOREIGN KEY(CNIC) REFERENCES Credentials(CNIC),
    FOREIGN KEY(Symbol) REFERENCES Companies(Symbol)
);
```

* Transaction
``` sql
CREATE TABLE Transactions (
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Buyer_CNIC TEXT NOT NULL,
    Seller_CNIC TEXT NOT NULL CHECK(Buyer_CNIC != Seller_CNIC),
    Symbol TEXT NOT NULL,
    Price INT NOT NULL CHECK(Price > 0),
    Lot_Count INT NOT NULL CHECK(Lot_Count > 0),
    DateOf DATE NOT NULL DEFAULT (date('now', 'localtime')),
    FOREIGN KEY(Buyer_CNIC) REFERENCES Credentials(CNIC),
    FOREIGN KEY(Seller_CNIC) REFERENCES Credentials(CNIC),
    FOREIGN KEY(Symbol) REFERENCES Companies(Symbol)
);
```