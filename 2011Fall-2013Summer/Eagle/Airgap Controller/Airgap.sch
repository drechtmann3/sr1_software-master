<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.3">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="7" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="7" fill="1" visible="no" active="no"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="relay">
<description>&lt;b&gt;Relays&lt;/b&gt;&lt;p&gt;
&lt;ul&gt;
&lt;li&gt;Eichhoff
&lt;li&gt;Finder
&lt;li&gt;Fujitsu
&lt;li&gt;HAMLIN
&lt;li&gt;OMRON
&lt;li&gt;Matsushita
&lt;li&gt;NAiS
&lt;li&gt;Siemens
&lt;li&gt;Schrack
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="G2R2">
<description>&lt;b&gt;RELAY&lt;/b&gt;&lt;p&gt;
2 x switch, Omron</description>
<wire x1="-4.699" y1="-6.604" x2="24.384" y2="-6.604" width="0.1524" layer="21"/>
<wire x1="24.384" y1="6.477" x2="24.384" y2="-6.604" width="0.1524" layer="21"/>
<wire x1="24.384" y1="6.477" x2="-4.699" y2="6.477" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="-6.604" x2="-4.699" y2="6.477" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="2.0574" x2="-2.54" y2="1.1938" width="0.1524" layer="21"/>
<wire x1="-0.6604" y1="1.1938" x2="-0.6604" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="-4.4196" y1="-1.3208" x2="-4.4196" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-4.4196" y1="1.1938" x2="-2.54" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-2.54" y1="1.1938" x2="-1.2954" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-3.7846" y1="-1.3208" x2="-4.4196" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="-1.2954" y1="1.1938" x2="-3.7846" y2="-1.3208" width="0.1524" layer="21"/>
<wire x1="-1.2954" y1="1.1938" x2="-0.6604" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-0.6604" y1="-1.3208" x2="-2.54" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-1.3208" x2="-2.54" y2="-1.9304" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.3208" x2="-3.7846" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="16.637" y1="0.508" x2="16.9672" y2="0.8382" width="0.254" layer="21"/>
<wire x1="16.9672" y1="0.8382" x2="12.446" y2="0.8382" width="0.1524" layer="21"/>
<wire x1="16.9672" y1="0.8382" x2="17.526" y2="1.397" width="0.254" layer="21"/>
<wire x1="12.446" y1="0.8382" x2="12.446" y2="1.9812" width="0.1524" layer="21"/>
<wire x1="18.4912" y1="0.8382" x2="22.479" y2="0.8382" width="0.1524" layer="21"/>
<wire x1="22.479" y1="0.8382" x2="22.479" y2="1.9812" width="0.1524" layer="21"/>
<wire x1="17.526" y1="1.905" x2="17.526" y2="1.397" width="0.1524" layer="21"/>
<wire x1="16.637" y1="-0.381" x2="16.9672" y2="-0.7112" width="0.254" layer="21"/>
<wire x1="16.9672" y1="-0.7112" x2="12.446" y2="-0.7112" width="0.1524" layer="21"/>
<wire x1="16.9672" y1="-0.7112" x2="17.526" y2="-1.27" width="0.254" layer="21"/>
<wire x1="12.446" y1="-0.7112" x2="12.446" y2="-1.8542" width="0.1524" layer="21"/>
<wire x1="18.4912" y1="-0.7112" x2="22.479" y2="-0.7112" width="0.1524" layer="21"/>
<wire x1="22.479" y1="-0.7112" x2="22.479" y2="-1.8542" width="0.1524" layer="21"/>
<wire x1="17.526" y1="-1.778" x2="17.526" y2="-1.27" width="0.1524" layer="21"/>
<pad name="2" x="-2.54" y="3.81" drill="1.3208" shape="long" rot="R90"/>
<pad name="1" x="-2.54" y="-3.683" drill="1.3208" shape="long" rot="R90"/>
<pad name="O1" x="12.4714" y="3.81" drill="1.3208" shape="long" rot="R90"/>
<pad name="P1" x="17.4498" y="3.81" drill="1.3208" shape="long" rot="R90"/>
<pad name="S1" x="22.4536" y="3.81" drill="1.3208" shape="long" rot="R90"/>
<pad name="O2" x="12.4714" y="-3.683" drill="1.3208" shape="long" rot="R90"/>
<pad name="P2" x="17.4498" y="-3.683" drill="1.3208" shape="long" rot="R90"/>
<pad name="S2" x="22.4536" y="-3.683" drill="1.3208" shape="long" rot="R90"/>
<text x="26.6446" y="-6.2992" size="1.778" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.81" y="-5.08" size="1.778" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="G2R2A">
<description>&lt;b&gt;RELAY&lt;/b&gt;&lt;p&gt;
2 x norm. open, Omron</description>
<wire x1="-4.699" y1="-6.604" x2="24.384" y2="-6.604" width="0.1524" layer="21"/>
<wire x1="24.384" y1="6.477" x2="24.384" y2="-6.604" width="0.1524" layer="21"/>
<wire x1="24.384" y1="6.477" x2="-4.699" y2="6.477" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="-6.604" x2="-4.699" y2="6.477" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="2.0574" x2="-2.54" y2="1.1938" width="0.1524" layer="21"/>
<wire x1="-0.6604" y1="1.1938" x2="-0.6604" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="-4.4196" y1="-1.3208" x2="-4.4196" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-4.4196" y1="1.1938" x2="-2.54" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-2.54" y1="1.1938" x2="-1.2954" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-3.7846" y1="-1.3208" x2="-4.4196" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="-1.2954" y1="1.1938" x2="-3.7846" y2="-1.3208" width="0.1524" layer="21"/>
<wire x1="-1.2954" y1="1.1938" x2="-0.6604" y2="1.1938" width="0.254" layer="21"/>
<wire x1="-0.6604" y1="-1.3208" x2="-2.54" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-1.3208" x2="-2.54" y2="-1.9304" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.3208" x2="-3.7846" y2="-1.3208" width="0.254" layer="21"/>
<wire x1="17.018" y1="0.889" x2="17.526" y2="1.397" width="0.1524" layer="21"/>
<wire x1="18.1102" y1="0.8382" x2="22.479" y2="0.8382" width="0.1524" layer="21"/>
<wire x1="22.479" y1="0.8382" x2="22.479" y2="1.9812" width="0.1524" layer="21"/>
<wire x1="17.526" y1="1.905" x2="17.526" y2="1.397" width="0.1524" layer="21"/>
<wire x1="17.018" y1="-0.762" x2="17.526" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="18.1102" y1="-0.7112" x2="22.479" y2="-0.7112" width="0.1524" layer="21"/>
<wire x1="22.479" y1="-0.7112" x2="22.479" y2="-1.8542" width="0.1524" layer="21"/>
<wire x1="17.526" y1="-1.778" x2="17.526" y2="-1.27" width="0.1524" layer="21"/>
<pad name="2" x="-2.54" y="3.81" drill="1.3208" shape="long" rot="R90"/>
<pad name="1" x="-2.54" y="-3.683" drill="1.3208" shape="long" rot="R90"/>
<pad name="P1" x="17.4498" y="3.81" drill="1.3208" shape="long" rot="R90"/>
<pad name="S1" x="22.4536" y="3.81" drill="1.3208" shape="long" rot="R90"/>
<pad name="P2" x="17.4498" y="-3.683" drill="1.3208" shape="long" rot="R90"/>
<pad name="S2" x="22.4536" y="-3.683" drill="1.3208" shape="long" rot="R90"/>
<text x="26.6446" y="-6.2992" size="1.778" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.81" y="-5.08" size="1.778" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="K">
<wire x1="-3.81" y1="-1.905" x2="-1.905" y2="-1.905" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.905" x2="3.81" y2="1.905" width="0.254" layer="94"/>
<wire x1="3.81" y1="1.905" x2="1.905" y2="1.905" width="0.254" layer="94"/>
<wire x1="-3.81" y1="1.905" x2="-3.81" y2="-1.905" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="0" y1="-1.905" x2="3.81" y2="-1.905" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="94"/>
<wire x1="0" y1="1.905" x2="-3.81" y2="1.905" width="0.254" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="1.905" y2="1.905" width="0.1524" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.905" x2="0" y2="1.905" width="0.254" layer="94"/>
<text x="1.27" y="2.921" size="1.778" layer="96">&gt;VALUE</text>
<text x="1.27" y="5.08" size="1.778" layer="95">&gt;PART</text>
<pin name="2" x="0" y="-5.08" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="1" x="0" y="5.08" visible="pad" length="short" direction="pas" rot="R270"/>
</symbol>
<symbol name="U">
<wire x1="3.175" y1="5.08" x2="1.905" y2="5.08" width="0.254" layer="94"/>
<wire x1="-3.175" y1="5.08" x2="-1.905" y2="5.08" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="2.54" y2="5.715" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="0" width="0.254" layer="94"/>
<circle x="0" y="1.27" radius="0.127" width="0.4064" layer="94"/>
<text x="2.54" y="0" size="1.778" layer="95">&gt;PART</text>
<pin name="O" x="5.08" y="5.08" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="S" x="-5.08" y="5.08" visible="pad" length="short" direction="pas"/>
<pin name="P" x="0" y="-2.54" visible="pad" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="S">
<wire x1="0" y1="3.175" x2="0" y2="1.905" width="0.254" layer="94"/>
<wire x1="0" y1="-3.175" x2="0" y2="-1.905" width="0.254" layer="94"/>
<wire x1="0" y1="-1.905" x2="-1.27" y2="1.905" width="0.254" layer="94"/>
<circle x="0" y="-1.905" radius="0.127" width="0.4064" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="95" rot="R90">&gt;PART</text>
<pin name="P" x="0" y="-5.08" visible="pad" length="short" direction="pas" swaplevel="1" rot="R90"/>
<pin name="S" x="0" y="5.08" visible="pad" length="short" direction="pas" swaplevel="1" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="G2R2" prefix="K">
<description>&lt;b&gt;RELAY&lt;/b&gt;&lt;p&gt;
2 x switch, Omron</description>
<gates>
<gate name="1" symbol="K" x="0" y="0" addlevel="must"/>
<gate name="2" symbol="U" x="17.78" y="5.08" addlevel="always" swaplevel="1"/>
<gate name="3" symbol="U" x="17.78" y="-7.62" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="G2R2">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="2" pin="O" pad="O1"/>
<connect gate="2" pin="P" pad="P1"/>
<connect gate="2" pin="S" pad="S1"/>
<connect gate="3" pin="O" pad="O2"/>
<connect gate="3" pin="P" pad="P2"/>
<connect gate="3" pin="S" pad="S2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="OMRON COMPONENTS USA" constant="no"/>
<attribute name="MPN" value="G2R-2-DC6" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="89C5317" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="G2R2A" prefix="K">
<description>&lt;b&gt;RELAY&lt;/b&gt;&lt;p&gt;
2 x norm. open, Omron</description>
<gates>
<gate name="1" symbol="K" x="0" y="0" addlevel="must"/>
<gate name="2" symbol="S" x="15.24" y="0" addlevel="always" swaplevel="1"/>
<gate name="3" symbol="S" x="22.86" y="0" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="G2R2A">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="2" pin="P" pad="P1"/>
<connect gate="2" pin="S" pad="S1"/>
<connect gate="3" pin="P" pad="P2"/>
<connect gate="3" pin="S" pad="S2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="G2R-2A-DC24" constant="no"/>
<attribute name="OC_FARNELL" value="6985269" constant="no"/>
<attribute name="OC_NEWARK" value="36M5257" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-amp">
<description>&lt;b&gt;AMP Connectors&lt;/b&gt;&lt;p&gt;
RJ45 Jack connectors&lt;br&gt;
 Based on the previous libraris:
 &lt;ul&gt;
 &lt;li&gt;amp.lbr
 &lt;li&gt;amp-j.lbr
 &lt;li&gt;amp-mta.lbr
 &lt;li&gt;amp-nlok.lbr
 &lt;li&gt;amp-sim.lbr
 &lt;li&gt;amp-micro-match.lbr
 &lt;/ul&gt;
 Sources :
 &lt;ul&gt;
 &lt;li&gt;Catalog 82066 Revised 11-95 
 &lt;li&gt;Product Guide 296785 Rev. 8-99
 &lt;li&gt;Product Guide CD-ROM 1999
 &lt;li&gt;www.amp.com
 &lt;/ul&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="794681-2">
<description>&lt;b&gt;Micro MATE-N-LOK Connectors&lt;/b&gt; grid 1.5mm&lt;p&gt;
Dual Row Through Hole Vertical Metal Through Hole Holddowns&lt;br&gt;
Source: ENG_CD_794681_E.pdf</description>
<wire x1="-1.825" y1="3.325" x2="1.825" y2="3.325" width="0.2032" layer="21"/>
<wire x1="1.825" y1="3.325" x2="1.825" y2="-3.325" width="0.2032" layer="21"/>
<wire x1="1.825" y1="-3.325" x2="-1.825" y2="-3.325" width="0.2032" layer="21"/>
<wire x1="-1.825" y1="-3.325" x2="-1.825" y2="3.325" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-2" x2="-3.4" y2="-1.1" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="-1.1" x2="-3.4" y2="1.1" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="1.1" x2="-2.5" y2="2" width="0.2032" layer="21"/>
<wire x1="2.5" y1="2" x2="3.4" y2="1.1" width="0.2032" layer="21"/>
<wire x1="3.4" y1="1.1" x2="3.4" y2="-1.1" width="0.2032" layer="21"/>
<wire x1="3.4" y1="-1.1" x2="2.5" y2="-2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="2" x2="-2.5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="1.5" x2="-2.5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.5" x2="-2.5" y2="-2" width="0.2032" layer="21"/>
<wire x1="2.5" y1="2" x2="2.5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="2.5" y1="1.5" x2="2.5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-1.5" x2="2.5" y2="-2" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-1.5" x2="2" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="2.5" y1="1.5" x2="2" y2="1.5" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="1.5" x2="-2" y2="1.5" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.5" x2="-2" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="1.55" y1="3.325" x2="0.775" y2="4.1" width="0.2032" layer="21" curve="-90"/>
<wire x1="0.775" y1="4.1" x2="0.775" y2="4.5" width="0.2032" layer="21"/>
<wire x1="-0.775" y1="4.5" x2="0.775" y2="4.5" width="0.2032" layer="21"/>
<wire x1="-0.775" y1="4.1" x2="-0.775" y2="4.5" width="0.2032" layer="21"/>
<wire x1="-0.775" y1="4.1" x2="-1.55" y2="3.325" width="0.2032" layer="21" curve="-90"/>
<wire x1="0.75" y1="4" x2="-0.75" y2="4" width="0.2032" layer="21"/>
<wire x1="-0.75" y1="0.25" x2="1.25" y2="0.25" width="0.2032" layer="21"/>
<wire x1="1.25" y1="0.25" x2="1.25" y2="2.75" width="0.2032" layer="21"/>
<wire x1="1.25" y1="2.75" x2="-1.25" y2="2.75" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="2.75" x2="-1.25" y2="0.75" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="-0.25" x2="-1.25" y2="-2.75" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="-2.75" x2="0.75" y2="-2.75" width="0.2032" layer="21"/>
<wire x1="1.25" y1="-2.25" x2="1.25" y2="-0.25" width="0.2032" layer="21"/>
<wire x1="0.75" y1="-2.75" x2="1.25" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-0.75" y1="0.25" x2="-1.25" y2="0.75" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="-0.25" x2="1.25" y2="-0.25" width="0.2032" layer="21"/>
<pad name="1" x="0" y="-1.5" drill="1" diameter="1.778"/>
<pad name="2" x="0" y="1.5" drill="1" diameter="1.778"/>
<text x="-3" y="-6" size="1.27" layer="25">&gt;NAME</text>
<text x="-3" y="4.5" size="1.27" layer="27">&gt;VALUE</text>
<hole x="2.13" y="0" drill="2.4"/>
<hole x="-2.17" y="0" drill="2.4"/>
</package>
<package name="350428-1">
<description>&lt;b&gt;Universal MATE-N-LOK&lt;/b&gt; .250" Centerline, 600 V, 19 - 36 A max&lt;p&gt;
Source: http://catalog.tycoelectronics.com/ .. ENG_CD_350428_Y.pdf</description>
<wire x1="-6.1593" y1="-2.9846" x2="-6.1593" y2="0" width="0.2032" layer="21"/>
<wire x1="-5.7783" y1="-2.6036" x2="-5.7783" y2="0" width="0.2032" layer="21"/>
<wire x1="-5.7783" y1="-2.6036" x2="-6.1593" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="6.1596" y1="-2.9846" x2="0.1907" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="-0.1903" y1="-2.9846" x2="-6.1593" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="5.7786" y1="-2.6036" x2="0.5717" y2="-2.6036" width="0.2032" layer="21"/>
<wire x1="-0.5713" y1="-2.6036" x2="-5.7783" y2="-2.6036" width="0.2032" layer="21"/>
<wire x1="-0.5713" y1="-2.6036" x2="-0.1903" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="-0.5713" y1="0" x2="-0.5713" y2="-2.6036" width="0.2032" layer="21"/>
<wire x1="-0.1903" y1="0" x2="-0.1903" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="0.1907" y1="-2.9846" x2="0.1907" y2="0" width="0.2032" layer="21"/>
<wire x1="0.5717" y1="-2.6036" x2="0.5717" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.1903" y1="0" x2="-0.1907" y2="0" width="0.2032" layer="21"/>
<wire x1="0.5717" y1="-2.6036" x2="0.1907" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="5.7786" y1="-2.6036" x2="6.1596" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="5.7786" y1="0" x2="5.7786" y2="-2.6036" width="0.2032" layer="21"/>
<wire x1="6.1596" y1="0" x2="6.1596" y2="-2.9846" width="0.2032" layer="21"/>
<wire x1="-6.1596" y1="0.0636" x2="-0.1907" y2="0.0636" width="0.2032" layer="21" curve="-177.354971"/>
<wire x1="0.1903" y1="0.0636" x2="6.1593" y2="0.0636" width="0.2032" layer="21" curve="-177.358853"/>
<wire x1="-5.7786" y1="0.0636" x2="-0.5717" y2="0.0636" width="0.2032" layer="21" curve="-177.095614"/>
<wire x1="0.5713" y1="0.0636" x2="5.7783" y2="0.0636" width="0.2032" layer="21" curve="-177.012098"/>
<wire x1="0.5713" y1="0" x2="0.5713" y2="0.0636" width="0.2032" layer="21"/>
<wire x1="0.1903" y1="0" x2="0.1903" y2="0.0636" width="0.2032" layer="21"/>
<wire x1="-0.1907" y1="0.0636" x2="-0.1907" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.5717" y1="0.0636" x2="-0.5717" y2="0" width="0.2032" layer="21"/>
<wire x1="-6.875" y1="3.7" x2="6.875" y2="3.7" width="0.2032" layer="21"/>
<wire x1="6.875" y1="3.7" x2="6.875" y2="1.175" width="0.2032" layer="21"/>
<wire x1="6.875" y1="1.175" x2="6.875" y2="1.15" width="0.2032" layer="21"/>
<wire x1="6.875" y1="1.175" x2="7.225" y2="1.175" width="0.2032" layer="21"/>
<wire x1="7.225" y1="1.175" x2="7.225" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="7.225" y1="-1.175" x2="6.875" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="6.875" y1="-1.175" x2="6.875" y2="-3.7" width="0.2032" layer="21"/>
<wire x1="6.875" y1="-3.7" x2="-6.875" y2="-3.7" width="0.2032" layer="21"/>
<wire x1="-6.875" y1="-3.7" x2="-6.875" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="-6.875" y1="-1.175" x2="-7.225" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="-7.225" y1="-1.175" x2="-7.225" y2="1.175" width="0.2032" layer="21"/>
<wire x1="-7.225" y1="1.175" x2="-6.875" y2="1.175" width="0.2032" layer="21"/>
<wire x1="-6.875" y1="1.175" x2="-6.875" y2="3.7" width="0.2032" layer="21"/>
<wire x1="-7.25" y1="1.175" x2="-9.425" y2="1.175" width="0.2032" layer="21"/>
<wire x1="-9.425" y1="1.175" x2="-9.425" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="-9.425" y1="-1.175" x2="-7.25" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="7.25" y1="1.175" x2="9.425" y2="1.175" width="0.2032" layer="21"/>
<wire x1="9.425" y1="1.175" x2="9.425" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="9.425" y1="-1.175" x2="7.25" y2="-1.175" width="0.2032" layer="21"/>
<wire x1="6.875" y1="-3.75" x2="6.875" y2="-4.975" width="0.2032" layer="21"/>
<wire x1="6.875" y1="-4.975" x2="5.825" y2="-4.975" width="0.2032" layer="21"/>
<wire x1="5.825" y1="-4.975" x2="5.825" y2="-3.825" width="0.2032" layer="21"/>
<wire x1="0.525" y1="-3.775" x2="0.525" y2="-4.975" width="0.2032" layer="21"/>
<wire x1="0.525" y1="-4.975" x2="-0.525" y2="-4.975" width="0.2032" layer="21"/>
<wire x1="-0.525" y1="-4.975" x2="-0.525" y2="-3.775" width="0.2032" layer="21"/>
<wire x1="-6.875" y1="-3.725" x2="-6.875" y2="-4.975" width="0.2032" layer="21"/>
<wire x1="-6.875" y1="-4.975" x2="-5.825" y2="-4.975" width="0.2032" layer="21"/>
<wire x1="-5.825" y1="-4.975" x2="-5.825" y2="-3.8" width="0.2032" layer="21"/>
<circle x="3.175" y="0" radius="1.5876" width="0.2032" layer="51"/>
<circle x="-3.175" y="0" radius="1.5877" width="0.2032" layer="51"/>
<pad name="1" x="-3.175" y="0" drill="1.8" diameter="3.81"/>
<pad name="2" x="3.175" y="0" drill="1.8" diameter="3.81"/>
<text x="0" y="2.54" size="1.016" layer="21" rot="SR90">1</text>
<text x="6.477" y="2.54" size="1.016" layer="21" rot="SR90">2</text>
<text x="-6.985" y="4.445" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.635" y="4.445" size="1.27" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="P2-2">
<wire x1="3.81" y1="-1.27" x2="-4.445" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-4.445" y1="1.27" x2="-4.445" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-4.445" y1="1.27" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.27" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<circle x="-2.54" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="2.54" y="0" radius="0.635" width="0.254" layer="94"/>
<text x="-5.08" y="-3.81" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="2.54" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.524" y="-0.508" size="1.27" layer="95">1</text>
<text x="1.524" y="0.762" size="1.27" layer="95" rot="R180">2</text>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="MTA-1_2">
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.905" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.905" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<circle x="0" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="2.54" y="0" radius="0.635" width="0.254" layer="94"/>
<text x="5.08" y="0" size="1.778" layer="95">&gt;NAME</text>
<text x="5.08" y="-3.81" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="-1.27" size="1.27" layer="95">1</text>
<pin name="1" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="2" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="794681-2" prefix="J">
<description>&lt;b&gt;Micro MATE-N-LOK Connectors&lt;/b&gt; grid 1.5mm&lt;p&gt;
Dual Row Through Hole Vertical Metal Through Hole Holddowns&lt;br&gt;
Source: ENG_CD_794681_E.pdf</description>
<gates>
<gate name="G$1" symbol="P2-2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="794681-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="350428-1" prefix="J">
<description>&lt;b&gt;Universal MATE-N-LOK&lt;/b&gt; .250" Centerline, 600 V, 19 - 36 A max&lt;p&gt;
Source: http://catalog.tycoelectronics.com/ .. ENG_CD_350428_Y.pdf</description>
<gates>
<gate name="G$1" symbol="MTA-1_2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="350428-1">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diode">
<description>&lt;b&gt;Diodes&lt;/b&gt;&lt;p&gt;
Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Motorola : www.onsemi.com
&lt;li&gt;Fairchild : www.fairchildsemi.com
&lt;li&gt;Philips : www.semiconductors.com
&lt;li&gt;Vishay : www.vishay.de
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="P6T15">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 9 mm, horizontal, grid 15.24 mm</description>
<wire x1="-4.699" y1="-4.572" x2="-4.699" y2="4.572" width="0.1524" layer="21"/>
<wire x1="4.699" y1="4.572" x2="4.699" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="4.572" x2="4.699" y2="4.572" width="0.1524" layer="21"/>
<wire x1="4.699" y1="-4.572" x2="-4.699" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0" x2="6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-7.62" y1="0" x2="-6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-0.381" y1="0.508" x2="-0.381" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.381" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.508" x2="0.381" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-7.62" y="0" drill="1.4986" shape="long"/>
<pad name="A" x="7.62" y="0" drill="1.4986" shape="long"/>
<text x="-4.6736" y="4.8514" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.3622" y="-3.302" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.429" y1="-4.572" x2="-2.921" y2="4.572" layer="21"/>
<rectangle x1="4.699" y1="-0.635" x2="5.969" y2="0.635" layer="21"/>
<rectangle x1="-5.969" y1="-0.635" x2="-4.699" y2="0.635" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="SCHOTTKY">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="1.016" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="-1.016" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<text x="-2.286" y="1.905" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.286" y="-3.429" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="5KPXX" prefix="D">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
transient voltage suppressor</description>
<gates>
<gate name="1" symbol="SCHOTTKY" x="0" y="0"/>
</gates>
<devices>
<device name="" package="P6T15">
<connects>
<connect gate="1" pin="A" pad="A"/>
<connect gate="1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SolarJacketsADC">
<packages>
<package name="SOT23">
<description>&lt;b&gt;SMALL OUTLINE TRANSISTOR&lt;/b&gt;&lt;p&gt;
reflow soldering</description>
<wire x1="-1.973" y1="1.983" x2="1.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="1.973" y1="-1.983" x2="-1.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-1.973" y1="-1.983" x2="-1.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="1.973" y1="1.983" x2="1.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="1.422" y1="0.66" x2="1.422" y2="-0.66" width="0.1524" layer="51"/>
<wire x1="1.422" y1="-0.66" x2="-1.422" y2="-0.66" width="0.1524" layer="51"/>
<wire x1="-1.422" y1="-0.66" x2="-1.422" y2="0.66" width="0.1524" layer="51"/>
<wire x1="-1.422" y1="0.66" x2="1.422" y2="0.66" width="0.1524" layer="51"/>
<smd name="3" x="0" y="1.1" dx="1" dy="1.4" layer="1"/>
<smd name="2" x="0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<smd name="1" x="-0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2286" y1="0.7112" x2="0.2286" y2="1.2954" layer="51"/>
<rectangle x1="0.7112" y1="-1.2954" x2="1.1684" y2="-0.7112" layer="51"/>
<rectangle x1="-1.1684" y1="-1.2954" x2="-0.7112" y2="-0.7112" layer="51"/>
<rectangle x1="-0.5001" y1="-0.3" x2="0.5001" y2="0.3" layer="35"/>
</package>
<package name="SOT223">
<description>&lt;b&gt;SMALL OUTLINE TRANSISTOR&lt;/b&gt;</description>
<wire x1="3.277" y1="1.778" x2="3.277" y2="-1.778" width="0.2032" layer="21"/>
<wire x1="3.277" y1="-1.778" x2="-3.277" y2="-1.778" width="0.2032" layer="21"/>
<wire x1="-3.277" y1="-1.778" x2="-3.277" y2="1.778" width="0.2032" layer="21"/>
<wire x1="-3.277" y1="1.778" x2="3.277" y2="1.778" width="0.2032" layer="21"/>
<wire x1="-3.473" y1="4.483" x2="3.473" y2="4.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-4.483" x2="-3.473" y2="-4.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-4.483" x2="-3.473" y2="4.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="4.483" x2="3.473" y2="-4.483" width="0.0508" layer="39"/>
<smd name="1" x="-2.311" y="-3.099" dx="1.219" dy="2.235" layer="1"/>
<smd name="2" x="0" y="-3.099" dx="1.219" dy="2.235" layer="1"/>
<smd name="3" x="2.311" y="-3.099" dx="1.219" dy="2.235" layer="1"/>
<smd name="4" x="0" y="3.099" dx="3.6" dy="2.2" layer="1"/>
<text x="-2.54" y="0.0508" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-1.3208" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.6002" y1="1.8034" x2="1.6002" y2="3.6576" layer="51"/>
<rectangle x1="-0.4318" y1="-3.6576" x2="0.4318" y2="-1.8034" layer="51"/>
<rectangle x1="-2.7432" y1="-3.6576" x2="-1.8796" y2="-1.8034" layer="51"/>
<rectangle x1="1.8796" y1="-3.6576" x2="2.7432" y2="-1.8034" layer="51"/>
<rectangle x1="-1.6002" y1="1.8034" x2="1.6002" y2="3.6576" layer="51"/>
<rectangle x1="-0.4318" y1="-3.6576" x2="0.4318" y2="-1.8034" layer="51"/>
<rectangle x1="-2.7432" y1="-3.6576" x2="-1.8796" y2="-1.8034" layer="51"/>
<rectangle x1="1.8796" y1="-3.6576" x2="2.7432" y2="-1.8034" layer="51"/>
<rectangle x1="-1" y1="-1" x2="1" y2="1" layer="35"/>
</package>
<package name="R1206">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;</description>
<wire x1="0.9525" y1="-0.8128" x2="-0.9652" y2="-0.8128" width="0.1524" layer="51"/>
<wire x1="0.9525" y1="0.8128" x2="-0.9652" y2="0.8128" width="0.1524" layer="51"/>
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<smd name="2" x="1.422" y="0" dx="1.6" dy="1.803" layer="1"/>
<smd name="1" x="-1.422" y="0" dx="1.6" dy="1.803" layer="1"/>
<text x="-1.27" y="1.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.6891" y1="-0.8763" x2="-0.9525" y2="0.8763" layer="51"/>
<rectangle x1="0.9525" y1="-0.8763" x2="1.6891" y2="0.8763" layer="51"/>
<rectangle x1="-0.3" y1="-0.7" x2="0.3" y2="0.7" layer="35"/>
</package>
<package name="0207/10">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
type 0207, grid 10 mm</description>
<wire x1="5.08" y1="0" x2="4.064" y2="0" width="0.6096" layer="51"/>
<wire x1="-5.08" y1="0" x2="-4.064" y2="0" width="0.6096" layer="51"/>
<wire x1="-3.175" y1="0.889" x2="-2.921" y2="1.143" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.175" y1="-0.889" x2="-2.921" y2="-1.143" width="0.1524" layer="21" curve="90"/>
<wire x1="2.921" y1="-1.143" x2="3.175" y2="-0.889" width="0.1524" layer="21" curve="90"/>
<wire x1="2.921" y1="1.143" x2="3.175" y2="0.889" width="0.1524" layer="21" curve="-90"/>
<wire x1="-3.175" y1="-0.889" x2="-3.175" y2="0.889" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="1.143" x2="-2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="1.016" x2="-2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="-1.143" x2="-2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="-2.413" y1="-1.016" x2="-2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="2.413" y1="1.016" x2="2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="2.413" y1="1.016" x2="-2.413" y2="1.016" width="0.1524" layer="21"/>
<wire x1="2.413" y1="-1.016" x2="2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="2.413" y1="-1.016" x2="-2.413" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.143" x2="2.54" y2="1.143" width="0.1524" layer="21"/>
<wire x1="2.921" y1="-1.143" x2="2.54" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-0.889" x2="3.175" y2="0.889" width="0.1524" layer="21"/>
<pad name="1" x="-5.08" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="5.08" y="0" drill="0.8128" shape="octagon"/>
<text x="-3.048" y="1.524" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.2606" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="3.175" y1="-0.3048" x2="4.0386" y2="0.3048" layer="21"/>
<rectangle x1="-4.0386" y1="-0.3048" x2="-3.175" y2="0.3048" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="MFNS">
<wire x1="-1.1176" y1="2.413" x2="-1.1176" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-1.1176" y1="-2.54" x2="-2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="1.905" x2="0.5334" y2="1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="0.508" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="1.905" x2="5.08" y2="1.905" width="0.1524" layer="94"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.08" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="4.445" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="4.445" y1="-0.635" x2="5.715" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="5.715" y1="-0.635" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="4.445" y1="0.762" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.715" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.715" y1="0.762" x2="5.969" y2="1.016" width="0.1524" layer="94"/>
<wire x1="4.445" y1="0.762" x2="4.191" y2="0.508" width="0.1524" layer="94"/>
<wire x1="0.508" y1="0" x2="1.778" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-0.508" x2="1.778" y2="0.508" width="0.1524" layer="94"/>
<wire x1="1.778" y1="0.508" x2="0.508" y2="0" width="0.1524" layer="94"/>
<wire x1="1.651" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="1.651" y1="0.254" x2="0.762" y2="0" width="0.3048" layer="94"/>
<wire x1="0.762" y1="0" x2="1.651" y2="-0.254" width="0.3048" layer="94"/>
<wire x1="1.651" y1="-0.254" x2="1.651" y2="0" width="0.3048" layer="94"/>
<wire x1="1.651" y1="0" x2="1.397" y2="0" width="0.3048" layer="94"/>
<circle x="2.54" y="-1.905" radius="0.127" width="0.4064" layer="94"/>
<circle x="2.54" y="1.905" radius="0.127" width="0.4064" layer="94"/>
<text x="7.62" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="7.62" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="1.27" y="2.54" size="0.8128" layer="93">D</text>
<text x="1.27" y="-3.175" size="0.8128" layer="93">S</text>
<text x="-2.54" y="-1.27" size="0.8128" layer="93">G</text>
<rectangle x1="-0.254" y1="-2.54" x2="0.508" y2="-1.27" layer="94"/>
<rectangle x1="-0.254" y1="1.27" x2="0.508" y2="2.54" layer="94"/>
<rectangle x1="-0.254" y1="-0.889" x2="0.508" y2="0.889" layer="94"/>
<pin name="G" x="-2.54" y="-2.54" visible="off" length="point" direction="pas"/>
<pin name="D" x="2.54" y="5.08" visible="off" length="short" direction="pas" rot="R270"/>
<pin name="S" x="2.54" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="R-US">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.2032" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.2032" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.2032" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.2032" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.2032" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.2032" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="N-CHANNEL_MOSFET">
<gates>
<gate name="G$1" symbol="MFNS" x="-2.54" y="0"/>
</gates>
<devices>
<device name="" package="SOT23">
<connects>
<connect gate="G$1" pin="D" pad="3"/>
<connect gate="G$1" pin="G" pad="1"/>
<connect gate="G$1" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="PMV56XN,215">
<attribute name="PART_NUM" value="PMV56XN,215"/>
</technology>
</technologies>
</device>
<device name="&quot;" package="SOT223">
<connects>
<connect gate="G$1" pin="D" pad="2 4"/>
<connect gate="G$1" pin="G" pad="1"/>
<connect gate="G$1" pin="S" pad="3"/>
</connects>
<technologies>
<technology name="NDT3055">
<attribute name="PART_NUM" value="NDT3055" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RESISTOR">
<gates>
<gate name="G$1" symbol="R-US" x="0" y="0"/>
</gates>
<devices>
<device name="SMD1206" package="R1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PART_NUM" value="" constant="no"/>
</technology>
</technologies>
</device>
<device name="THROUGH_HOLE" package="0207/10">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
<class number="1" name="power" width="2.54" drill="76.2">
</class>
</classes>
<parts>
<part name="K1" library="relay" deviceset="G2R2" device=""/>
<part name="K2" library="relay" deviceset="G2R2A" device=""/>
<part name="R1" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R2" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="T1" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN"/>
<part name="T2" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN"/>
<part name="OUTPUT" library="con-amp" deviceset="350428-1" device="">
<attribute name="NEG" value="-"/>
<attribute name="POS" value="+"/>
</part>
<part name="POWER" library="con-amp" deviceset="350428-1" device=""/>
<part name="IO" library="con-amp" deviceset="794681-2" device=""/>
<part name="R3" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R4" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R5" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="0">
<attribute name="PART_NUM" value="CR1206-J/-000ELF"/>
</part>
<part name="R6" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="0">
<attribute name="PART_NUM" value="CR1206-J/-000ELF"/>
</part>
<part name="D3" library="diode" deviceset="5KPXX" device="" value="6A4"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="K1" gate="1" x="-12.7" y="53.34"/>
<instance part="K1" gate="2" x="66.04" y="20.32" rot="R270"/>
<instance part="K1" gate="3" x="66.04" y="73.66" rot="R270"/>
<instance part="K2" gate="1" x="10.16" y="53.34"/>
<instance part="K2" gate="2" x="50.8" y="73.66" rot="R270"/>
<instance part="K2" gate="3" x="50.8" y="20.32" rot="R270"/>
<instance part="R1" gate="G$1" x="-12.7" y="66.04" rot="R90"/>
<instance part="R2" gate="G$1" x="10.16" y="66.04" rot="R90"/>
<instance part="T1" gate="G$1" x="-15.24" y="40.64"/>
<instance part="T2" gate="G$1" x="7.62" y="40.64"/>
<instance part="OUTPUT" gate="G$1" x="142.24" y="55.88" rot="R270">
<attribute name="NEG" x="142.24" y="55.88" size="1.778" layer="96" rot="R270" display="off"/>
<attribute name="POS" x="142.24" y="55.88" size="1.778" layer="96" rot="R270" display="off"/>
</instance>
<instance part="POWER" gate="G$1" x="-45.72" y="40.64" rot="R90"/>
<instance part="IO" gate="G$1" x="-45.72" y="7.62" rot="R90"/>
<instance part="R3" gate="G$1" x="-22.86" y="12.7" rot="R180"/>
<instance part="R4" gate="G$1" x="0" y="2.54" rot="R180"/>
<instance part="R5" gate="G$1" x="-12.7" y="27.94" rot="R90"/>
<instance part="R6" gate="G$1" x="10.16" y="27.94" rot="R90"/>
<instance part="D3" gate="1" x="-30.48" y="60.96" smashed="yes" rot="R90"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="1">
<segment>
<pinref part="K2" gate="2" pin="S"/>
<pinref part="K1" gate="3" pin="P"/>
<wire x1="63.5" y1="73.66" x2="55.88" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="1">
<segment>
<pinref part="K2" gate="3" pin="S"/>
<pinref part="K1" gate="2" pin="P"/>
<wire x1="63.5" y1="20.32" x2="55.88" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="12V" class="1">
<segment>
<wire x1="10.16" y1="73.66" x2="-12.7" y2="73.66" width="0.1524" layer="91"/>
<wire x1="10.16" y1="73.66" x2="10.16" y2="71.12" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="2"/>
<wire x1="-12.7" y1="73.66" x2="-12.7" y2="71.12" width="0.1524" layer="91"/>
<wire x1="-12.7" y1="73.66" x2="-30.48" y2="73.66" width="0.1524" layer="91"/>
<junction x="-12.7" y="73.66"/>
<pinref part="K2" gate="2" pin="P"/>
<wire x1="10.16" y1="73.66" x2="45.72" y2="73.66" width="0.1524" layer="91"/>
<junction x="10.16" y="73.66"/>
<pinref part="R2" gate="G$1" pin="2"/>
<pinref part="D3" gate="1" pin="C"/>
<wire x1="-30.48" y1="73.66" x2="-30.48" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="1">
<segment>
<pinref part="K2" gate="3" pin="P"/>
<pinref part="POWER" gate="G$1" pin="1"/>
<wire x1="-30.48" y1="20.32" x2="-12.7" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-12.7" y1="20.32" x2="10.16" y2="20.32" width="0.1524" layer="91"/>
<wire x1="10.16" y1="20.32" x2="45.72" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="40.64" x2="-30.48" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-30.48" y1="40.64" x2="-30.48" y2="20.32" width="0.1524" layer="91"/>
<label x="-40.64" y="40.64" size="1.778" layer="95"/>
<pinref part="R5" gate="G$1" pin="1"/>
<wire x1="-12.7" y1="22.86" x2="-12.7" y2="20.32" width="0.1524" layer="91"/>
<junction x="-12.7" y="20.32"/>
<pinref part="R6" gate="G$1" pin="1"/>
<wire x1="10.16" y1="22.86" x2="10.16" y2="20.32" width="0.1524" layer="91"/>
<junction x="10.16" y="20.32"/>
</segment>
</net>
<net name="MOTOR-" class="1">
<segment>
<pinref part="K1" gate="2" pin="O"/>
<wire x1="71.12" y1="15.24" x2="71.12" y2="12.7" width="0.1524" layer="91"/>
<wire x1="71.12" y1="12.7" x2="111.76" y2="12.7" width="0.1524" layer="91"/>
<wire x1="111.76" y1="12.7" x2="111.76" y2="55.88" width="0.1524" layer="91"/>
<pinref part="K1" gate="3" pin="S"/>
<wire x1="111.76" y1="55.88" x2="111.76" y2="81.28" width="0.1524" layer="91"/>
<wire x1="71.12" y1="78.74" x2="71.12" y2="81.28" width="0.1524" layer="91"/>
<wire x1="71.12" y1="81.28" x2="111.76" y2="81.28" width="0.1524" layer="91"/>
<pinref part="OUTPUT" gate="G$1" pin="1"/>
<label x="127" y="55.88" size="1.778" layer="95"/>
<junction x="111.76" y="55.88"/>
<wire x1="111.76" y1="55.88" x2="139.7" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="1"/>
<pinref part="K1" gate="1" pin="1"/>
<wire x1="-12.7" y1="58.42" x2="-12.7" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="1"/>
<pinref part="K2" gate="1" pin="1"/>
<wire x1="10.16" y1="58.42" x2="10.16" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="K1" gate="1" pin="2"/>
<pinref part="T1" gate="G$1" pin="D"/>
<wire x1="-12.7" y1="45.72" x2="-12.7" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="K2" gate="1" pin="2"/>
<pinref part="T2" gate="G$1" pin="D"/>
<wire x1="10.16" y1="45.72" x2="10.16" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="T2" gate="G$1" pin="G"/>
<wire x1="5.08" y1="38.1" x2="5.08" y2="2.54" width="0.1524" layer="91"/>
<pinref part="R4" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="T1" gate="G$1" pin="G"/>
<wire x1="-17.78" y1="38.1" x2="-17.78" y2="12.7" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="1"/>
</segment>
</net>
<net name="DIR" class="0">
<segment>
<pinref part="IO" gate="G$1" pin="2"/>
<pinref part="R3" gate="G$1" pin="2"/>
<wire x1="-45.72" y1="12.7" x2="-27.94" y2="12.7" width="0.1524" layer="91"/>
<label x="-40.64" y="12.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="ON" class="0">
<segment>
<pinref part="IO" gate="G$1" pin="1"/>
<pinref part="R4" gate="G$1" pin="2"/>
<wire x1="-45.72" y1="2.54" x2="-5.08" y2="2.54" width="0.1524" layer="91"/>
<label x="-40.64" y="2.54" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="T1" gate="G$1" pin="S"/>
<pinref part="R5" gate="G$1" pin="2"/>
<wire x1="-12.7" y1="35.56" x2="-12.7" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="T2" gate="G$1" pin="S"/>
<pinref part="R6" gate="G$1" pin="2"/>
<wire x1="10.16" y1="35.56" x2="10.16" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="12V_PRE" class="1">
<segment>
<pinref part="POWER" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="43.18" x2="-30.48" y2="43.18" width="0.1524" layer="91"/>
<label x="-40.64" y="43.18" size="1.778" layer="95"/>
<pinref part="D3" gate="1" pin="A"/>
<wire x1="-30.48" y1="58.42" x2="-30.48" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="MOTOR+" class="1">
<segment>
<pinref part="K1" gate="2" pin="S"/>
<wire x1="71.12" y1="25.4" x2="71.12" y2="27.94" width="0.1524" layer="91"/>
<wire x1="71.12" y1="27.94" x2="104.14" y2="27.94" width="0.1524" layer="91"/>
<pinref part="K1" gate="3" pin="O"/>
<wire x1="71.12" y1="68.58" x2="71.12" y2="66.04" width="0.1524" layer="91"/>
<wire x1="71.12" y1="66.04" x2="104.14" y2="66.04" width="0.1524" layer="91"/>
<wire x1="104.14" y1="27.94" x2="104.14" y2="53.34" width="0.1524" layer="91"/>
<pinref part="OUTPUT" gate="G$1" pin="2"/>
<wire x1="104.14" y1="53.34" x2="104.14" y2="66.04" width="0.1524" layer="91"/>
<label x="127" y="50.8" size="1.778" layer="95"/>
<junction x="104.14" y="53.34"/>
<wire x1="139.7" y1="53.34" x2="104.14" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
