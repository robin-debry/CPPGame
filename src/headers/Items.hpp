class Items
{
    public:
        void PlaceItem(int x, int y, int z, int itemID);
        void Sprites();
        int Size;
};

class Coins : public Items
{
    public:
        void PlaceItem(int x, int y, int z, int itemID);
        void Sprites();
        int Size;
        int value;
};

class Missiles : public Items
{
    public:
        void PlaceItem(int x, int y, int z, int itemID);
        void Sprites();
        int Size;
        int speed;
        int direction;
};

void Coins::PlaceItem(int x, int y, int z, int itemID)
{
    // Place coin at x, y, z
}

void Missiles::PlaceItem(int x, int y, int z, int itemID)
{
    // Place missile at x, y, z
}

void Coins::Sprites()
{
    // Draw coin sprite
}

void Missiles::Sprites()
{
    // Draw missile sprite
}