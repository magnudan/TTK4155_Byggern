library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity address_decoder is
	Port (
		-- in
		a11 : In std_logic;
		a10 : In std_logic;
		a9 	: In std_logic;
		a8 	: In std_logic;
		-- out
		ram_cs 	: Out std_logic;
		adc_cs 	: Out std_logic;	
		oled_cs	: Out std_logic;
		oled_dc	: Out std_logic -- Not necessary…
	);
	attribute LOC : string;
	attribute LOC of ram_cs		: signal is "P19";
	attribute LOC of adc_cs		: signal is "P18";
	attribute LOC of oled_cs 	: signal is "P17";
	attribute LOC of oled_dc	: signal is "P16"; -- Not necessary…
	
	attribute LOC of a11 	: signal is "P1";
	attribute LOC of a10 	: signal is "P2";
	attribute LOC of a9 	: signal is "P3";
	attribute LOC of a8 	: signal is "P4";
end address_decoder;

architecture behave of address_decoder is begin
	if (a11) then
		ram_cs <= '1';
	elsif (a10) then
		adc_cs <= '1';
	elsif (a9) then
		oled_dc <= '1';
	else
		oled_cs <= '1';
	end if;
end behave;