#include "color.h"

Color_t::Color_t( const int r, const int g, const int b, const int a )
	: r( r )
	  , g( g )
	  , b( b )
	  , a( a ) {}

Color_t::Color_t( const float r, const float g, const float b, const float a )
	: r( static_cast<uint8_t>(r * 255.f) )
	  , g( static_cast<uint8_t>(g * 255.f) )
	  , b( static_cast<uint8_t>(b * 255.f) )
	  , a( static_cast<uint8_t>(a * 255.f) ) {}

int& Color_t::operator[]( size_t i ) noexcept {
	return reinterpret_cast<int*>(this)[i];
}

int Color_t::operator[]( size_t i ) const noexcept {
	return reinterpret_cast<const int*>(this)[i];
}

unsigned int Color_t::GetU32() const noexcept {
	unsigned int out = r << 0;
	out |= g << 8;
	out |= b << 16;
	out |= a << 24;
	return out;
}
