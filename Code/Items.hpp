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