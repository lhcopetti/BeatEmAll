#pragma once

class TiledLayerTile
{
private:
	bool _hFlipped;
	bool _vFlipped;
	bool _dFlipped;

	int _gid;

public:
	TiledLayerTile();
	TiledLayerTile(unsigned int gid);

	void init(unsigned int gid);

	int gid() const { return _gid; };
	void setGid(unsigned int gid);

	bool hFlipped() const { return _hFlipped; };
	bool vFlipped() const { return _vFlipped; };
	bool dFlipped() const { return _dFlipped; };

	static bool isHFlipped(unsigned int gid);
	static bool isVFlipped(unsigned int gid);
	static bool isDFlipped(unsigned int gid);
};