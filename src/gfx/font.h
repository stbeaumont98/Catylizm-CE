static unsigned char font_spacing[128] =
{
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 3, 4, 6, 4, 6, 5, 2, 3, 3, 4, 4, 3, 4, 3, 5,
    6, 4, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 5, 5, 5, 6, 5, 5,
    5, 5, 5, 5, 6, 5, 5, 6, 6, 5, 5, 3, 5, 3, 6, 5,
    3, 5, 5, 5, 5, 5, 5, 5, 5, 2, 5, 5, 5, 6, 5, 5,
    5, 5, 5, 4, 4, 5, 5, 6, 5, 5, 5, 5, 2, 5, 5, 5
};

unsigned char font[128 * 8] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 000 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 001 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 002 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 003 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 004 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 005 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 006 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 007 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 008 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 009 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 010 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 011 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 012 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 013 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 014 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 015 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 016 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 017 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 018 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 019 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 020 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 021 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 022 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 023 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 024 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 025 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 026 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 027 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 028 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 029 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 030 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 031 (.)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 032 ( )
	0xC0, 0xC0, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x00,	// Char 033 (!)
	0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 034 (")
	0x50, 0xF8, 0x50, 0xF8, 0x50, 0x00, 0x00, 0x00,	// Char 035 (#)
	0x40, 0xE0, 0xC0, 0x60, 0xE0, 0x40, 0x00, 0x00,	// Char 036 ($)
	0xC8, 0xD0, 0x20, 0x58, 0x98, 0x00, 0x00, 0x00,	// Char 037 (%)
	0x40, 0xA0, 0x50, 0xA0, 0x50, 0x00, 0x00, 0x00,	// Char 038 (&)
	0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 039 (')
	0x40, 0x80, 0x80, 0x80, 0x40, 0x00, 0x00, 0x00,	// Char 040 (()
	0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00,	// Char 041 ())
	0xA0, 0x40, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 042 (*)
	0x00, 0x40, 0xE0, 0x40, 0x00, 0x00, 0x00, 0x00,	// Char 043 (+)
	0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00,	// Char 044 (,)
	0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 045 (-)
	0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00,	// Char 046 (.)
	0x10, 0x10, 0x60, 0x80, 0x80, 0x00, 0x00, 0x00,	// Char 047 (/)
	0x70, 0x98, 0xA8, 0xC8, 0x70, 0x00, 0x00, 0x00,	// Char 048 (0)
	0x40, 0xC0, 0x40, 0x40, 0xE0, 0x00, 0x00, 0x00,	// Char 049 (1)
	0x60, 0x90, 0x20, 0x40, 0xF0, 0x00, 0x00, 0x00,	// Char 050 (2)
	0xE0, 0x10, 0x60, 0x10, 0xE0, 0x00, 0x00, 0x00,	// Char 051 (3)
	0x90, 0x90, 0xF0, 0x10, 0x10, 0x00, 0x00, 0x00,	// Char 052 (4)
	0xF0, 0x80, 0xF0, 0x10, 0xF0, 0x00, 0x00, 0x00,	// Char 053 (5)
	0xF0, 0x80, 0xF0, 0x90, 0xF0, 0x00, 0x00, 0x00,	// Char 054 (6)
	0xF0, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00,	// Char 055 (7)
	0x60, 0x90, 0x60, 0x90, 0x60, 0x00, 0x00, 0x00,	// Char 056 (8)
	0x60, 0x90, 0x90, 0x70, 0x10, 0x00, 0x00, 0x00,	// Char 057 (9)
	0x00, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00,	// Char 058 (:)
	0x00, 0xC0, 0x00, 0x40, 0x80, 0x00, 0x00, 0x00,	// Char 059 (;)
	0x10, 0x60, 0x80, 0x60, 0x10, 0x00, 0x00, 0x00,	// Char 060 (<)
	0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00,	// Char 061 (=)
	0x80, 0x60, 0x10, 0x60, 0x80, 0x00, 0x00, 0x00,	// Char 062 (>)
	0x60, 0x90, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00,	// Char 063 (?)
	0x60, 0x90, 0xB0, 0x80, 0x70, 0x00, 0x00, 0x00,	// Char 064 (@)
	0x60, 0x90, 0x90, 0xF0, 0x90, 0x00, 0x00, 0x00,	// Char 065 (A)
	0xE0, 0x90, 0xE0, 0x90, 0xE0, 0x00, 0x00, 0x00,	// Char 066 (B)
	0x60, 0x90, 0x80, 0x90, 0x60, 0x00, 0x00, 0x00,	// Char 067 (C)
	0xE0, 0x90, 0x90, 0x90, 0xE0, 0x00, 0x00, 0x00,	// Char 068 (D)
	0xF0, 0x90, 0xC0, 0x90, 0xF0, 0x00, 0x00, 0x00,	// Char 069 (E)
	0xF0, 0x90, 0x80, 0xC0, 0x80, 0x00, 0x00, 0x00,	// Char 070 (F)
	0x70, 0x80, 0xB0, 0x90, 0xF0, 0x00, 0x00, 0x00,	// Char 071 (G)
	0x90, 0x90, 0xF0, 0x90, 0x90, 0x00, 0x00, 0x00,	// Char 072 (H)
	0xE0, 0x40, 0x40, 0x40, 0xE0, 0x00, 0x00, 0x00,	// Char 073 (I)
	0x30, 0x10, 0x10, 0x90, 0x60, 0x00, 0x00, 0x00,	// Char 074 (J)
	0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x00, 0x00, 0x00,	// Char 075 (K)
	0x80, 0x80, 0x80, 0x80, 0xF0, 0x00, 0x00, 0x00,	// Char 076 (L)
	0x88, 0xD8, 0xA8, 0x88, 0x88, 0x00, 0x00, 0x00,	// Char 077 (M)
	0x90, 0xD0, 0xB0, 0x90, 0x90, 0x00, 0x00, 0x00,	// Char 078 (N)
	0x60, 0x90, 0x90, 0x90, 0x60, 0x00, 0x00, 0x00,	// Char 079 (O)
	0x60, 0x90, 0x90, 0xE0, 0x80, 0x00, 0x00, 0x00,	// Char 080 (P)
	0x60, 0x90, 0x90, 0x90, 0x78, 0x00, 0x00, 0x00,	// Char 081 (Q)
	0xE0, 0x90, 0x90, 0xE0, 0x90, 0x00, 0x00, 0x00,	// Char 082 (R)
	0xF0, 0x80, 0x60, 0x10, 0xF0, 0x00, 0x00, 0x00,	// Char 083 (S)
	0xF8, 0xA8, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,	// Char 084 (T)
	0x90, 0x90, 0x90, 0x90, 0x70, 0x00, 0x00, 0x00,	// Char 085 (U)
	0x90, 0x90, 0x90, 0x50, 0x20, 0x00, 0x00, 0x00,	// Char 086 (V)
	0x88, 0x88, 0xA8, 0xA8, 0x50, 0x00, 0x00, 0x00,	// Char 087 (W)
	0x88, 0x50, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00,	// Char 088 (X)
	0x90, 0x90, 0xF0, 0x10, 0xF0, 0x00, 0x00, 0x00,	// Char 089 (Y)
	0xF0, 0x10, 0x60, 0x80, 0xF0, 0x00, 0x00, 0x00,	// Char 090 (Z)
	0xC0, 0x80, 0x80, 0x80, 0xC0, 0x00, 0x00, 0x00,	// Char 091 ([)
	0x80, 0x80, 0x60, 0x10, 0x10, 0x00, 0x00, 0x00,	// Char 092 (\)
	0xC0, 0x40, 0x40, 0x40, 0xC0, 0x00, 0x00, 0x00,	// Char 093 (])
	0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 094 (^)
	0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00,	// Char 095 (_)
	0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 096 (`)
	0x00, 0x60, 0x90, 0x90, 0x70, 0x00, 0x00, 0x00,	// Char 097 (a)
	0x80, 0xE0, 0x90, 0x90, 0xE0, 0x00, 0x00, 0x00,	// Char 098 (b)
	0x00, 0x70, 0x80, 0x80, 0x70, 0x00, 0x00, 0x00,	// Char 099 (c)
	0x10, 0x70, 0x90, 0x90, 0x70, 0x00, 0x00, 0x00,	// Char 100 (d)
	0x60, 0x90, 0xF0, 0x80, 0x60, 0x00, 0x00, 0x00,	// Char 101 (e)
	0x60, 0x90, 0x80, 0xC0, 0x80, 0x00, 0x00, 0x00,	// Char 102 (f)
	0x60, 0x90, 0x70, 0x10, 0x60, 0x00, 0x00, 0x00,	// Char 103 (g)
	0x80, 0xE0, 0x90, 0x90, 0x90, 0x00, 0x00, 0x00,	// Char 104 (h)
	0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,	// Char 105 (i)
	0x10, 0x00, 0x10, 0x90, 0x60, 0x00, 0x00, 0x00,	// Char 106 (j)
	0x80, 0x90, 0x90, 0xE0, 0x90, 0x00, 0x00, 0x00,	// Char 107 (k)
	0x80, 0x80, 0x80, 0x80, 0x60, 0x00, 0x00, 0x00,	// Char 108 (l)
	0x00, 0x50, 0xA8, 0xA8, 0xA8, 0x00, 0x00, 0x00,	// Char 109 (m)
	0x00, 0xE0, 0x90, 0x90, 0x90, 0x00, 0x00, 0x00,	// Char 110 (n)
	0x00, 0x60, 0x90, 0x90, 0x60, 0x00, 0x00, 0x00,	// Char 111 (o)
	0x00, 0x60, 0x90, 0xE0, 0x80, 0x00, 0x00, 0x00,	// Char 112 (p)
	0x00, 0x60, 0x90, 0x70, 0x10, 0x00, 0x00, 0x00,	// Char 113 (q)
	0x00, 0x60, 0x90, 0x80, 0x80, 0x00, 0x00, 0x00,	// Char 114 (r)
	0x00, 0xE0, 0xC0, 0x20, 0xE0, 0x00, 0x00, 0x00,	// Char 115 (s)
	0x40, 0x40, 0xE0, 0x40, 0x40, 0x00, 0x00, 0x00,	// Char 116 (t)
	0x00, 0x90, 0x90, 0x90, 0x70, 0x00, 0x00, 0x00,	// Char 117 (u)
	0x00, 0x90, 0x90, 0x50, 0x20, 0x00, 0x00, 0x00,	// Char 118 (v)
	0x00, 0x88, 0xA8, 0xA8, 0x50, 0x00, 0x00, 0x00,	// Char 119 (w)
	0x00, 0x90, 0x60, 0x60, 0x90, 0x00, 0x00, 0x00,	// Char 120 (x)
	0x00, 0x90, 0x50, 0x20, 0xC0, 0x00, 0x00, 0x00,	// Char 121 (y)
	0x00, 0xF0, 0x20, 0x40, 0xF0, 0x00, 0x00, 0x00,	// Char 122 (z)
	0x70, 0x40, 0x80, 0x40, 0x70, 0x00, 0x00, 0x00,	// Char 123 ({)
	0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,	// Char 124 (|)
	0xE0, 0x20, 0x10, 0x20, 0xE0, 0x00, 0x00, 0x00,	// Char 125 (})
	0x50, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 126 (~)
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Char 127 (.)
};

