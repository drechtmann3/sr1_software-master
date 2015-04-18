<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
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
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="tOverhead" color="7" fill="1" visible="yes" active="yes"/>
<layer number="101" name="Frame" color="4" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="7" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="7" fill="1" visible="no" active="no"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
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
<library name="SolarJackets_Common">
<description>Parts used in Solar Jackets boards. Common library for all components.</description>
<packages>
<package name="MA14-2">
<wire x1="-12.065" y1="2.54" x2="-10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="2.54" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="2.54" x2="-12.7" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.54" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="1.905" x2="-12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="-2.54" x2="-12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-2.54" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-11.43" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-11.43" y="1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<text x="-11.938" y="-4.191" size="1.27" layer="21" ratio="10">1</text>
<text x="-12.7" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="2.54" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="3.81" y="2.921" size="1.27" layer="21" ratio="10">20</text>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-11.684" y1="-1.524" x2="-11.176" y2="-1.016" layer="51"/>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="-11.684" y1="1.016" x2="-11.176" y2="1.524" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<hole x="-20.32" y="0" drill="2.6924"/>
<hole x="12.7" y="0" drill="2.6924"/>
<wire x1="-37.973" y1="4.2672" x2="-24.384" y2="4.2672" width="0.127" layer="100" style="shortdash"/>
<wire x1="-24.384" y1="4.2672" x2="15.24" y2="4.2672" width="0.127" layer="21"/>
<wire x1="15.24" y1="4.2672" x2="16.764" y2="4.2672" width="0.127" layer="21"/>
<wire x1="16.764" y1="4.2672" x2="16.764" y2="-4.2672" width="0.127" layer="21"/>
<wire x1="16.764" y1="-4.2672" x2="16.51" y2="-4.2672" width="0.127" layer="21"/>
<wire x1="16.51" y1="-4.2672" x2="-24.384" y2="-4.2672" width="0.127" layer="21"/>
<wire x1="-24.384" y1="-4.2672" x2="-24.384" y2="4.2672" width="0.127" layer="21"/>
<wire x1="-37.973" y1="4.2672" x2="-37.973" y2="-4.2672" width="0.127" layer="100" style="shortdash"/>
<wire x1="-37.973" y1="-4.2672" x2="-24.384" y2="-4.2672" width="0.127" layer="100" style="shortdash"/>
<wire x1="15.24" y1="4.2672" x2="30.353" y2="4.2672" width="0.127" layer="100" style="shortdash"/>
<wire x1="30.353" y1="4.2672" x2="30.353" y2="-4.2672" width="0.127" layer="100" style="shortdash"/>
<wire x1="30.353" y1="-4.2672" x2="16.51" y2="-4.2672" width="0.127" layer="100" style="shortdash"/>
<circle x="-11.43" y="-5.08" radius="0.2032" width="0.4064" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="-1.905" width="0.127" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="MA14-2">
<wire x1="1.27" y1="17.78" x2="8.89" y2="17.78" width="0.4064" layer="94"/>
<wire x1="3.81" y1="12.7" x2="2.54" y2="12.7" width="0.6096" layer="94"/>
<wire x1="3.81" y1="15.24" x2="2.54" y2="15.24" width="0.6096" layer="94"/>
<wire x1="7.62" y1="12.7" x2="6.35" y2="12.7" width="0.6096" layer="94"/>
<wire x1="7.62" y1="15.24" x2="6.35" y2="15.24" width="0.6096" layer="94"/>
<wire x1="3.81" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="3.81" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="3.81" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="7.62" y1="5.08" x2="6.35" y2="5.08" width="0.6096" layer="94"/>
<wire x1="7.62" y1="7.62" x2="6.35" y2="7.62" width="0.6096" layer="94"/>
<wire x1="7.62" y1="10.16" x2="6.35" y2="10.16" width="0.6096" layer="94"/>
<wire x1="8.89" y1="-2.54" x2="8.89" y2="17.78" width="0.4064" layer="94"/>
<wire x1="1.27" y1="17.78" x2="1.27" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="8.89" y1="-2.54" x2="1.27" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="3.81" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="3.81" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="7.62" y1="0" x2="6.35" y2="0" width="0.6096" layer="94"/>
<wire x1="7.62" y1="2.54" x2="6.35" y2="2.54" width="0.6096" layer="94"/>
<text x="8.89" y="-3.302" size="1.778" layer="95" rot="R180">&gt;NAME</text>
<pin name="7" x="-2.54" y="15.24" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="9" x="-2.54" y="12.7" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="8" x="12.7" y="15.24" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="10" x="12.7" y="12.7" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="11" x="-2.54" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="13" x="-2.54" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="15" x="-2.54" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="12" x="12.7" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="14" x="12.7" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="16" x="12.7" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="17" x="-2.54" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="19" x="-2.54" y="0" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="18" x="12.7" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="20" x="12.7" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<wire x1="7.62" y1="12.7" x2="6.35" y2="12.7" width="0.6096" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="AMP_LATCH_14">
<gates>
<gate name="G$1" symbol="MA14-2" x="-2.54" y="-5.08"/>
</gates>
<devices>
<device name="" package="MA14-2">
<connects>
<connect gate="G$1" pin="10" pad="4"/>
<connect gate="G$1" pin="11" pad="5"/>
<connect gate="G$1" pin="12" pad="6"/>
<connect gate="G$1" pin="13" pad="7"/>
<connect gate="G$1" pin="14" pad="8"/>
<connect gate="G$1" pin="15" pad="9"/>
<connect gate="G$1" pin="16" pad="10"/>
<connect gate="G$1" pin="17" pad="11"/>
<connect gate="G$1" pin="18" pad="12"/>
<connect gate="G$1" pin="19" pad="13"/>
<connect gate="G$1" pin="20" pad="14"/>
<connect gate="G$1" pin="7" pad="1"/>
<connect gate="G$1" pin="8" pad="2"/>
<connect gate="G$1" pin="9" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-molex">
<description>&lt;b&gt;Molex Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="70543-03">
<description>&lt;b&gt;C-Grid SL Connector&lt;/b&gt;&lt;p&gt;
 vertical, 3 pin</description>
<wire x1="5.08" y1="-2.8575" x2="5.08" y2="2.8575" width="0.254" layer="21"/>
<wire x1="5.08" y1="2.8575" x2="-5.08" y2="2.8575" width="0.254" layer="21"/>
<wire x1="-5.08" y1="2.8575" x2="-5.08" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="-5.08" y1="-2.8575" x2="-3.4925" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="-3.4925" y1="-2.8575" x2="-3.4925" y2="-3.81" width="0.254" layer="21"/>
<wire x1="-3.4925" y1="-3.81" x2="3.4925" y2="-3.81" width="0.254" layer="21"/>
<wire x1="3.4925" y1="-3.81" x2="3.4925" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="3.4925" y1="-2.8575" x2="5.08" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="-4.445" y1="2.2225" x2="-4.445" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="4.445" y1="2.2225" x2="4.445" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="-4.445" y1="2.2225" x2="4.445" y2="2.2225" width="0.0508" layer="51"/>
<wire x1="-4.445" y1="-2.2225" x2="-2.8575" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="-2.8575" y1="-2.2225" x2="2.8575" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="2.8575" y1="-2.2225" x2="4.445" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="2.8575" y1="-3.175" x2="-2.8575" y2="-3.175" width="0.0508" layer="51"/>
<wire x1="-2.8575" y1="-2.2225" x2="-2.8575" y2="-3.175" width="0.0508" layer="51"/>
<wire x1="2.8575" y1="-2.2225" x2="2.8575" y2="-3.175" width="0.0508" layer="51"/>
<pad name="3" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="1" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-5.715" y="-2.54" size="1.016" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-4.7625" y="3.4925" size="0.8128" layer="27" ratio="10">&gt;VALUE</text>
<text x="-4.1275" y="-1.5875" size="1.016" layer="51" ratio="10">1</text>
<rectangle x1="-0.2381" y1="-0.2381" x2="0.2381" y2="0.2381" layer="51"/>
<rectangle x1="-2.7781" y1="-0.2381" x2="-2.3019" y2="0.2381" layer="51"/>
<rectangle x1="2.3019" y1="-0.2381" x2="2.7781" y2="0.2381" layer="51"/>
</package>
<package name="70553-03">
<description>&lt;b&gt;C-Grid SL Connector&lt;/b&gt;&lt;p&gt;
 right angle, 3 pin</description>
<wire x1="5.2388" y1="5.8738" x2="4.1275" y2="5.8738" width="0.254" layer="21"/>
<wire x1="4.1275" y1="5.8738" x2="-5.2387" y2="5.8738" width="0.254" layer="21"/>
<wire x1="-5.2387" y1="5.8738" x2="-5.2388" y2="-5.715" width="0.254" layer="21"/>
<wire x1="-1.27" y1="2.54" x2="-1.27" y2="-3.175" width="0.254" layer="21"/>
<wire x1="-1.27" y1="-3.175" x2="1.27" y2="-3.175" width="0.254" layer="21"/>
<wire x1="1.27" y1="-3.175" x2="1.27" y2="2.54" width="0.254" layer="21"/>
<wire x1="-4.1275" y1="5.8737" x2="-4.1275" y2="2.54" width="0.254" layer="21"/>
<wire x1="-4.1275" y1="2.54" x2="-3.175" y2="2.54" width="0.254" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-1.27" y2="2.54" width="0.254" layer="21"/>
<wire x1="1.27" y1="2.54" x2="3.175" y2="2.54" width="0.254" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.1275" y2="2.54" width="0.254" layer="21"/>
<wire x1="4.1275" y1="2.54" x2="4.1275" y2="5.8738" width="0.254" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-3.175" y2="3.175" width="0.254" layer="21"/>
<wire x1="-3.175" y1="3.175" x2="-1.905" y2="4.445" width="0.254" layer="21" curve="-90"/>
<wire x1="-1.905" y1="4.445" x2="1.905" y2="4.445" width="0.254" layer="21"/>
<wire x1="1.905" y1="4.445" x2="3.175" y2="3.175" width="0.254" layer="21" curve="-90"/>
<wire x1="3.175" y1="3.175" x2="3.175" y2="2.54" width="0.254" layer="21"/>
<wire x1="-5.2388" y1="-5.715" x2="5.2388" y2="-5.715" width="0.254" layer="21"/>
<wire x1="5.2388" y1="-5.715" x2="5.2388" y2="5.8738" width="0.254" layer="21"/>
<wire x1="-4.1275" y1="-5.715" x2="-4.1275" y2="-6.35" width="0.254" layer="51"/>
<wire x1="-4.1275" y1="-6.35" x2="-4.1275" y2="-7.9375" width="0.254" layer="51"/>
<wire x1="-4.1275" y1="-6.35" x2="-3.175" y2="-6.35" width="0.254" layer="51"/>
<wire x1="-3.175" y1="-6.35" x2="-1.905" y2="-6.35" width="0.127" layer="51"/>
<wire x1="-1.905" y1="-6.35" x2="-0.635" y2="-6.35" width="0.254" layer="51"/>
<wire x1="-0.635" y1="-6.35" x2="0.635" y2="-6.35" width="0.127" layer="51"/>
<wire x1="0.635" y1="-6.35" x2="1.5875" y2="-6.35" width="0.254" layer="51"/>
<wire x1="-3.175" y1="-6.35" x2="-3.175" y2="-7.6835" width="0.254" layer="51"/>
<wire x1="-3.175" y1="-7.6835" x2="-3.429" y2="-7.9375" width="0.254" layer="51" curve="-90"/>
<wire x1="-3.429" y1="-7.9375" x2="-4.1275" y2="-7.9375" width="0.254" layer="51"/>
<wire x1="-1.905" y1="-6.35" x2="-1.905" y2="-7.6835" width="0.254" layer="51"/>
<wire x1="-1.905" y1="-7.6835" x2="-1.651" y2="-7.9375" width="0.254" layer="51" curve="90"/>
<wire x1="-0.635" y1="-6.35" x2="-0.635" y2="-7.6835" width="0.254" layer="51"/>
<wire x1="-0.635" y1="-7.6835" x2="-0.889" y2="-7.9375" width="0.254" layer="51" curve="-90"/>
<wire x1="-0.889" y1="-7.9375" x2="-1.651" y2="-7.9375" width="0.254" layer="51"/>
<wire x1="0.635" y1="-6.35" x2="0.635" y2="-7.6835" width="0.254" layer="51"/>
<wire x1="0.635" y1="-7.6835" x2="0.889" y2="-7.9375" width="0.254" layer="51" curve="90"/>
<wire x1="0.889" y1="-7.9375" x2="1.3335" y2="-7.9375" width="0.254" layer="51"/>
<wire x1="1.3335" y1="-7.9375" x2="1.5875" y2="-7.6835" width="0.254" layer="51" curve="90"/>
<wire x1="1.5875" y1="-7.6835" x2="1.5875" y2="-6.35" width="0.254" layer="51"/>
<wire x1="4.1275" y1="-7.9375" x2="4.1275" y2="-6.35" width="0.254" layer="51"/>
<wire x1="4.1275" y1="-6.35" x2="4.1275" y2="-5.715" width="0.254" layer="51"/>
<wire x1="1.5875" y1="-6.35" x2="3.175" y2="-6.35" width="0.127" layer="51"/>
<wire x1="3.175" y1="-6.35" x2="4.1275" y2="-6.35" width="0.254" layer="51"/>
<wire x1="3.175" y1="-6.35" x2="3.175" y2="-7.6835" width="0.254" layer="51"/>
<wire x1="3.175" y1="-7.6835" x2="3.429" y2="-7.9375" width="0.254" layer="51" curve="90"/>
<wire x1="3.429" y1="-7.9375" x2="4.1275" y2="-7.9375" width="0.254" layer="51"/>
<pad name="2" x="0" y="-7.62" drill="1.0922" shape="long" rot="R90"/>
<pad name="1" x="-2.54" y="-7.62" drill="1.0922" shape="long" rot="R90"/>
<pad name="3" x="2.54" y="-7.62" drill="1.0922" shape="long" rot="R90"/>
<text x="-5.715" y="-5.715" size="1.016" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="6.985" y="-5.715" size="0.8128" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-2.8575" y1="-7.62" x2="-2.2225" y2="-6.35" layer="51"/>
<rectangle x1="-0.3175" y1="-7.62" x2="0.3175" y2="-6.35" layer="51"/>
<rectangle x1="2.2225" y1="-7.62" x2="2.8575" y2="-6.35" layer="51"/>
<polygon width="0.0508" layer="21">
<vertex x="-3.9688" y="5.8738"/>
<vertex x="-3.4924" y="3.9689"/>
<vertex x="-3.0163" y="5.8738"/>
</polygon>
</package>
<package name="74099-03">
<description>&lt;b&gt;C-Grid SL Connector&lt;/b&gt;&lt;p&gt;
 vertical SMD, 3 pin</description>
<wire x1="5.08" y1="-2.8575" x2="5.08" y2="2.8575" width="0.254" layer="21"/>
<wire x1="5.08" y1="2.8575" x2="-5.08" y2="2.8575" width="0.254" layer="21"/>
<wire x1="-5.08" y1="2.8575" x2="-5.08" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="-5.08" y1="-2.8575" x2="-3.4925" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="-3.4925" y1="-2.8575" x2="-3.4925" y2="-3.81" width="0.254" layer="21"/>
<wire x1="-3.4925" y1="-3.81" x2="3.4925" y2="-3.81" width="0.254" layer="21"/>
<wire x1="3.4925" y1="-3.81" x2="3.4925" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="3.4925" y1="-2.8575" x2="5.08" y2="-2.8575" width="0.254" layer="21"/>
<wire x1="-4.445" y1="2.2225" x2="-4.445" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="4.445" y1="2.2225" x2="4.445" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="-4.445" y1="2.2225" x2="4.445" y2="2.2225" width="0.0508" layer="51"/>
<wire x1="-4.445" y1="-2.2225" x2="-2.8575" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="-2.8575" y1="-2.2225" x2="2.8575" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="2.8575" y1="-2.2225" x2="4.445" y2="-2.2225" width="0.0508" layer="51"/>
<wire x1="2.8575" y1="-3.175" x2="-2.8575" y2="-3.175" width="0.0508" layer="51"/>
<wire x1="-2.8575" y1="-2.2225" x2="-2.8575" y2="-3.175" width="0.0508" layer="51"/>
<wire x1="2.8575" y1="-2.2225" x2="2.8575" y2="-3.175" width="0.0508" layer="51"/>
<smd name="3" x="2.54" y="-2.2225" dx="3.175" dy="1.27" layer="1" rot="R270"/>
<smd name="2" x="0" y="2.2225" dx="3.175" dy="1.27" layer="1" rot="R270"/>
<smd name="1" x="-2.54" y="-2.2225" dx="3.175" dy="1.27" layer="1" rot="R270"/>
<text x="-5.715" y="-2.54" size="1.016" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-4.1275" y="0.635" size="0.8128" layer="27" ratio="10">&gt;VALUE</text>
<text x="-4.1275" y="-1.905" size="1.016" layer="51" ratio="10">1</text>
<rectangle x1="-2.7781" y1="-0.2381" x2="-2.3019" y2="0.2381" layer="51"/>
<rectangle x1="2.3019" y1="-0.2381" x2="2.7781" y2="0.2381" layer="51"/>
<rectangle x1="-0.2381" y1="-0.2381" x2="0.2381" y2="0.2381" layer="51"/>
</package>
<package name="15-91-03">
<description>&lt;b&gt;C-Grid SL Connector&lt;/b&gt;&lt;p&gt;
 right angle SMD, 3 pin</description>
<wire x1="5.2388" y1="5.08" x2="-5.2387" y2="5.08" width="0.254" layer="21"/>
<wire x1="-5.2387" y1="5.08" x2="-5.2387" y2="2.2225" width="0.254" layer="21"/>
<wire x1="-5.2388" y1="-0.635" x2="-5.2388" y2="-6.35" width="0.254" layer="21"/>
<wire x1="-1.27" y1="1.905" x2="-1.27" y2="-3.81" width="0.254" layer="51"/>
<wire x1="-1.27" y1="-3.81" x2="1.27" y2="-3.81" width="0.254" layer="51"/>
<wire x1="1.27" y1="-3.81" x2="1.27" y2="1.905" width="0.254" layer="51"/>
<wire x1="-4.1275" y1="5.0799" x2="-4.1275" y2="1.905" width="0.254" layer="51"/>
<wire x1="-4.1275" y1="1.905" x2="-3.175" y2="1.905" width="0.254" layer="51"/>
<wire x1="-3.175" y1="1.905" x2="-1.27" y2="1.905" width="0.254" layer="51"/>
<wire x1="1.27" y1="1.905" x2="3.175" y2="1.905" width="0.254" layer="51"/>
<wire x1="3.175" y1="1.905" x2="4.1275" y2="1.905" width="0.254" layer="51"/>
<wire x1="4.1275" y1="1.905" x2="4.1275" y2="5.08" width="0.254" layer="51"/>
<wire x1="-3.175" y1="1.905" x2="-3.175" y2="2.54" width="0.254" layer="51"/>
<wire x1="-3.175" y1="2.54" x2="-1.905" y2="3.81" width="0.254" layer="51" curve="-90"/>
<wire x1="-1.905" y1="3.81" x2="1.905" y2="3.81" width="0.254" layer="51"/>
<wire x1="1.905" y1="3.81" x2="3.175" y2="2.54" width="0.254" layer="51" curve="-90"/>
<wire x1="3.175" y1="2.54" x2="3.175" y2="1.905" width="0.254" layer="51"/>
<wire x1="-5.2388" y1="-6.35" x2="5.2388" y2="-6.35" width="0.254" layer="21"/>
<wire x1="5.2388" y1="-6.35" x2="5.2388" y2="-0.635" width="0.254" layer="21"/>
<wire x1="5.2388" y1="2.2225" x2="5.2388" y2="5.08" width="0.254" layer="21"/>
<wire x1="-3.81" y1="-6.35" x2="-3.81" y2="-8.5725" width="0.254" layer="51"/>
<wire x1="-3.81" y1="-6.985" x2="-3.175" y2="-6.985" width="0.254" layer="51"/>
<wire x1="-1.905" y1="-6.985" x2="-0.635" y2="-6.985" width="0.254" layer="51"/>
<wire x1="-3.175" y1="-6.985" x2="-3.175" y2="-8.3185" width="0.254" layer="51"/>
<wire x1="-3.175" y1="-8.3185" x2="-3.429" y2="-8.5725" width="0.254" layer="51" curve="-90"/>
<wire x1="-3.429" y1="-8.5725" x2="-3.81" y2="-8.5725" width="0.254" layer="51"/>
<wire x1="-1.905" y1="-6.985" x2="-1.905" y2="-8.3185" width="0.254" layer="51"/>
<wire x1="-1.905" y1="-8.3185" x2="-1.651" y2="-8.5725" width="0.254" layer="51" curve="90"/>
<wire x1="-0.635" y1="-6.985" x2="-0.635" y2="-8.3185" width="0.254" layer="51"/>
<wire x1="-0.635" y1="-8.3185" x2="-0.889" y2="-8.5725" width="0.254" layer="51" curve="-90"/>
<wire x1="-0.889" y1="-8.5725" x2="-1.651" y2="-8.5725" width="0.254" layer="51"/>
<wire x1="3.81" y1="-8.5725" x2="3.81" y2="-6.35" width="0.254" layer="51"/>
<wire x1="0.635" y1="-6.985" x2="1.905" y2="-6.985" width="0.254" layer="51"/>
<wire x1="3.175" y1="-6.985" x2="3.81" y2="-6.985" width="0.254" layer="51"/>
<wire x1="0.635" y1="-6.985" x2="0.635" y2="-8.3185" width="0.254" layer="51"/>
<wire x1="0.635" y1="-8.3185" x2="0.889" y2="-8.5725" width="0.254" layer="51" curve="90"/>
<wire x1="1.905" y1="-6.985" x2="1.905" y2="-8.3185" width="0.254" layer="51"/>
<wire x1="1.905" y1="-8.3185" x2="1.651" y2="-8.5725" width="0.254" layer="51" curve="-90"/>
<wire x1="1.651" y1="-8.5725" x2="0.889" y2="-8.5725" width="0.254" layer="51"/>
<wire x1="3.175" y1="-6.985" x2="3.175" y2="-8.3185" width="0.254" layer="51"/>
<wire x1="3.175" y1="-8.3185" x2="3.429" y2="-8.5725" width="0.254" layer="51" curve="90"/>
<wire x1="3.429" y1="-8.5725" x2="3.81" y2="-8.5725" width="0.254" layer="51"/>
<wire x1="-5.2388" y1="2.2225" x2="-5.2388" y2="-0.635" width="0.254" layer="51"/>
<wire x1="5.2388" y1="2.2225" x2="5.2388" y2="-0.635" width="0.254" layer="51"/>
<wire x1="-3.175" y1="-6.985" x2="-1.905" y2="-6.985" width="0.254" layer="51"/>
<wire x1="-0.635" y1="-6.985" x2="0.635" y2="-6.985" width="0.254" layer="51"/>
<wire x1="1.905" y1="-6.985" x2="3.175" y2="-6.985" width="0.254" layer="51"/>
<smd name="1" x="-2.54" y="-10.795" dx="5.334" dy="1.651" layer="1" rot="R90"/>
<smd name="2" x="0" y="-10.795" dx="5.334" dy="1.651" layer="1" rot="R90"/>
<smd name="3" x="2.54" y="-10.795" dx="5.334" dy="1.651" layer="1" rot="R90"/>
<text x="-5.715" y="-6.35" size="1.016" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="6.985" y="-6.35" size="0.8128" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-2.8575" y1="-10.795" x2="-2.2225" y2="-6.985" layer="51"/>
<rectangle x1="-0.3175" y1="-10.795" x2="0.3175" y2="-6.985" layer="51"/>
<rectangle x1="2.2225" y1="-10.795" x2="2.8575" y2="-6.985" layer="51"/>
<hole x="-3.937" y="0.8382" drill="3.4036"/>
<hole x="3.937" y="0.8382" drill="3.4036"/>
<polygon width="0.2032" layer="21">
<vertex x="-3.81" y="5.08"/>
<vertex x="-3.3337" y="3.4926"/>
<vertex x="-2.8575" y="5.08"/>
</polygon>
</package>
</packages>
<symbols>
<symbol name="MV">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-0.762" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="C-GRID-03" prefix="X">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
wire to board 2.54 mm (0.100") pitch header</description>
<gates>
<gate name="-1" symbol="MV" x="2.54" y="7.62" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="2.54" y="5.08" addlevel="always" swaplevel="1"/>
<gate name="-3" symbol="M" x="2.54" y="2.54" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="-70543" package="70543-03">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="-70553" package="70553-03">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="-74099" package="74099-03">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="-15-91" package="15-91-03">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
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
</devicesets>
</library>
<library name="LTC6803">
<packages>
<package name="20MIL">
<pad name="P$1" x="0" y="0" drill="0.508" shape="octagon"/>
</package>
</packages>
<symbols>
<symbol name="PS">
<wire x1="0.635" y1="-4.572" x2="-0.635" y2="-4.572" width="0.1524" layer="94"/>
<wire x1="0.635" y1="-4.572" x2="0.635" y2="0" width="0.1524" layer="94"/>
<wire x1="0.635" y1="0" x2="-0.635" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-4.572" width="0.1524" layer="94"/>
<wire x1="0.381" y1="-3.048" x2="-0.381" y2="-2.794" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="-2.794" x2="0.381" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0.381" y1="-2.54" x2="-0.381" y2="-2.286" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="-2.286" x2="0.381" y2="-2.032" width="0.1524" layer="94"/>
<wire x1="0.381" y1="-2.032" x2="-0.381" y2="-1.778" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="-1.778" x2="0.381" y2="-1.524" width="0.1524" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="-0.381" y2="-1.27" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="-1.27" x2="0.381" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="0.381" y1="-1.016" x2="-0.381" y2="-0.762" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="-0.762" x2="0.381" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="0.508" y1="-5.207" x2="-0.508" y2="-5.207" width="0.1524" layer="94"/>
<wire x1="-0.508" y1="-5.207" x2="-0.508" y2="-5.715" width="0.1524" layer="94"/>
<wire x1="-0.508" y1="-5.715" x2="0" y2="-6.35" width="0.1524" layer="94"/>
<wire x1="0" y1="-6.35" x2="0.508" y2="-5.715" width="0.1524" layer="94"/>
<wire x1="0.508" y1="-5.715" x2="0.508" y2="-5.207" width="0.1524" layer="94"/>
<text x="-1.016" y="-6.35" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<rectangle x1="-0.381" y1="-5.207" x2="0.381" y2="-4.572" layer="94"/>
<pin name="TP" x="0" y="2.54" visible="off" length="short" direction="in" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="TESTPAD-20MIL">
<gates>
<gate name="G$1" symbol="PS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="20MIL">
<connects>
<connect gate="G$1" pin="TP" pad="P$1"/>
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
</classes>
<parts>
<part name="BRAKE-R1" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN215"/>
<part name="BLINKER-L1" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN215"/>
<part name="BLINKER-L2" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN215"/>
<part name="BLINKER-R1" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN215"/>
<part name="BLINKER-R2" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN215"/>
<part name="BRAKE-C1" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="N-CHANNEL_MOSFETPMV56XN,215">
<attribute name="PART_NUM" value="PMV56XN,215"/>
</part>
<part name="R1" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R3" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R5" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R6" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R14" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R15" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="BRAKE-L1" library="SolarJacketsADC" deviceset="N-CHANNEL_MOSFET" device="" technology="PMV56XN,215" value="PMV56XN215">
<attribute name="PART_NUM" value="PMV56XN,215"/>
</part>
<part name="R16" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R7" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R9" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="R10" library="SolarJacketsADC" deviceset="RESISTOR" device="SMD1206" value="1k">
<attribute name="PART_NUM" value="CR1206-FX-1001GLF"/>
</part>
<part name="U$1" library="SolarJackets_Common" deviceset="AMP_LATCH_14" device=""/>
<part name="X1" library="con-molex" deviceset="C-GRID-03" device="-70553"/>
<part name="J1" library="con-amp" deviceset="794681-2" device=""/>
<part name="BLRB" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BLRF" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BLLB" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BLLF" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BL" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BC" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BR" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BRC" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="BLC" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="B" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="12V" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
<part name="GND" library="LTC6803" deviceset="TESTPAD-20MIL" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="BRAKE-R1" gate="G$1" x="-27.94" y="78.74" smashed="yes">
<attribute name="NAME" x="-21.59" y="81.28" size="1.778" layer="95"/>
</instance>
<instance part="BLINKER-L1" gate="G$1" x="48.26" y="78.74" smashed="yes">
<attribute name="NAME" x="54.61" y="81.28" size="1.778" layer="95"/>
</instance>
<instance part="BLINKER-L2" gate="G$1" x="86.36" y="78.74" smashed="yes">
<attribute name="NAME" x="92.71" y="81.28" size="1.778" layer="95"/>
</instance>
<instance part="BLINKER-R1" gate="G$1" x="124.46" y="78.74" smashed="yes">
<attribute name="NAME" x="130.81" y="81.28" size="1.778" layer="95"/>
</instance>
<instance part="BLINKER-R2" gate="G$1" x="162.56" y="78.74" smashed="yes">
<attribute name="NAME" x="168.91" y="81.28" size="1.778" layer="95"/>
</instance>
<instance part="BRAKE-C1" gate="G$1" x="-88.9" y="78.74" smashed="yes">
<attribute name="NAME" x="-82.55" y="81.28" size="1.778" layer="95"/>
<attribute name="PART_NUM" x="-88.9" y="78.74" size="1.778" layer="96" display="off"/>
</instance>
<instance part="R1" gate="G$1" x="-104.14" y="71.12" rot="R90"/>
<instance part="R3" gate="G$1" x="-43.18" y="71.12" rot="R90"/>
<instance part="R5" gate="G$1" x="20.32" y="71.12" rot="R90"/>
<instance part="R6" gate="G$1" x="58.42" y="71.12" rot="R90"/>
<instance part="R14" gate="G$1" x="96.52" y="71.12" rot="R90"/>
<instance part="R15" gate="G$1" x="134.62" y="71.12" rot="R90"/>
<instance part="BRAKE-L1" gate="G$1" x="-149.86" y="78.74" smashed="yes">
<attribute name="NAME" x="-143.51" y="81.28" size="1.778" layer="95"/>
<attribute name="PART_NUM" x="-149.86" y="78.74" size="1.778" layer="96" display="off"/>
</instance>
<instance part="R16" gate="G$1" x="-165.1" y="71.12" rot="R90"/>
<instance part="R7" gate="G$1" x="86.36" y="2.54" smashed="yes">
<attribute name="VALUE" x="92.71" y="2.032" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="R9" gate="G$1" x="86.36" y="-2.54" smashed="yes" rot="R180">
<attribute name="VALUE" x="92.71" y="-3.048" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="R10" gate="G$1" x="86.36" y="0" smashed="yes" rot="R180">
<attribute name="VALUE" x="92.71" y="-0.508" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="U$1" gate="G$1" x="25.4" y="15.24"/>
<instance part="X1" gate="-1" x="93.98" y="2.54"/>
<instance part="X1" gate="-2" x="93.98" y="0"/>
<instance part="X1" gate="-3" x="93.98" y="-2.54"/>
<instance part="J1" gate="G$1" x="96.52" y="-10.16"/>
<instance part="BLRB" gate="G$1" x="68.58" y="30.48" rot="R90"/>
<instance part="BLRF" gate="G$1" x="68.58" y="27.94" rot="R90"/>
<instance part="BLLB" gate="G$1" x="68.58" y="25.4" rot="R90"/>
<instance part="BLLF" gate="G$1" x="68.58" y="22.86" rot="R90"/>
<instance part="BL" gate="G$1" x="68.58" y="20.32" rot="R90"/>
<instance part="BC" gate="G$1" x="68.58" y="17.78" rot="R90"/>
<instance part="BR" gate="G$1" x="68.58" y="15.24" rot="R90"/>
<instance part="BRC" gate="G$1" x="63.5" y="2.54" rot="R270"/>
<instance part="BLC" gate="G$1" x="63.5" y="0" rot="R270"/>
<instance part="B" gate="G$1" x="63.5" y="-2.54" rot="R270"/>
<instance part="12V" gate="G$1" x="81.28" y="-10.16" rot="R270"/>
<instance part="GND" gate="G$1" x="111.76" y="-10.16" rot="R90"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="BLINKER-R2" gate="G$1" pin="S"/>
<wire x1="-104.14" y1="63.5" x2="-86.36" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-86.36" y1="63.5" x2="-78.74" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="63.5" x2="-50.8" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-50.8" y1="63.5" x2="-43.18" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="63.5" x2="-25.4" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-25.4" y1="63.5" x2="-17.78" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-17.78" y1="63.5" x2="12.7" y2="63.5" width="0.1524" layer="91"/>
<wire x1="12.7" y1="63.5" x2="20.32" y2="63.5" width="0.1524" layer="91"/>
<wire x1="20.32" y1="63.5" x2="50.8" y2="63.5" width="0.1524" layer="91"/>
<wire x1="50.8" y1="63.5" x2="58.42" y2="63.5" width="0.1524" layer="91"/>
<wire x1="58.42" y1="63.5" x2="88.9" y2="63.5" width="0.1524" layer="91"/>
<wire x1="88.9" y1="63.5" x2="96.52" y2="63.5" width="0.1524" layer="91"/>
<wire x1="96.52" y1="63.5" x2="127" y2="63.5" width="0.1524" layer="91"/>
<wire x1="127" y1="63.5" x2="134.62" y2="63.5" width="0.1524" layer="91"/>
<wire x1="134.62" y1="63.5" x2="165.1" y2="63.5" width="0.1524" layer="91"/>
<pinref part="R15" gate="G$1" pin="1"/>
<wire x1="134.62" y1="66.04" x2="134.62" y2="63.5" width="0.1524" layer="91"/>
<junction x="134.62" y="63.5"/>
<pinref part="R14" gate="G$1" pin="1"/>
<wire x1="96.52" y1="66.04" x2="96.52" y2="63.5" width="0.1524" layer="91"/>
<junction x="96.52" y="63.5"/>
<wire x1="165.1" y1="73.66" x2="165.1" y2="63.5" width="0.1524" layer="91"/>
<pinref part="R6" gate="G$1" pin="1"/>
<wire x1="58.42" y1="66.04" x2="58.42" y2="63.5" width="0.1524" layer="91"/>
<junction x="58.42" y="63.5"/>
<pinref part="R5" gate="G$1" pin="1"/>
<wire x1="20.32" y1="66.04" x2="20.32" y2="63.5" width="0.1524" layer="91"/>
<junction x="20.32" y="63.5"/>
<pinref part="R3" gate="G$1" pin="1"/>
<wire x1="-43.18" y1="66.04" x2="-43.18" y2="63.5" width="0.1524" layer="91"/>
<junction x="-43.18" y="63.5"/>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="-104.14" y1="66.04" x2="-104.14" y2="63.5" width="0.1524" layer="91"/>
<pinref part="BRAKE-C1" gate="G$1" pin="S"/>
<wire x1="-86.36" y1="73.66" x2="-86.36" y2="63.5" width="0.1524" layer="91"/>
<junction x="-86.36" y="63.5"/>
<pinref part="BRAKE-R1" gate="G$1" pin="S"/>
<wire x1="-25.4" y1="73.66" x2="-25.4" y2="63.5" width="0.1524" layer="91"/>
<junction x="-25.4" y="63.5"/>
<pinref part="BLINKER-L1" gate="G$1" pin="S"/>
<wire x1="50.8" y1="73.66" x2="50.8" y2="63.5" width="0.1524" layer="91"/>
<junction x="50.8" y="63.5"/>
<wire x1="88.9" y1="73.66" x2="88.9" y2="63.5" width="0.1524" layer="91"/>
<junction x="88.9" y="63.5"/>
<pinref part="BLINKER-R1" gate="G$1" pin="S"/>
<wire x1="127" y1="73.66" x2="127" y2="63.5" width="0.1524" layer="91"/>
<junction x="127" y="63.5"/>
<pinref part="BLINKER-L2" gate="G$1" pin="S"/>
<wire x1="-165.1" y1="63.5" x2="-147.32" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-147.32" y1="63.5" x2="-139.7" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-139.7" y1="63.5" x2="-111.76" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-111.76" y1="63.5" x2="-104.14" y2="63.5" width="0.1524" layer="91"/>
<pinref part="R16" gate="G$1" pin="1"/>
<wire x1="-165.1" y1="66.04" x2="-165.1" y2="63.5" width="0.1524" layer="91"/>
<pinref part="BRAKE-L1" gate="G$1" pin="S"/>
<wire x1="-147.32" y1="73.66" x2="-147.32" y2="63.5" width="0.1524" layer="91"/>
<junction x="-147.32" y="63.5"/>
<junction x="-104.14" y="63.5"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="2"/>
<wire x1="101.6" y1="-10.16" x2="109.22" y2="-10.16" width="0.1524" layer="91"/>
<junction x="109.22" y="-10.16"/>
<label x="106.68" y="-10.16" size="1.778" layer="95"/>
<pinref part="GND" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BRAKE_L_-" class="0">
<segment>
<pinref part="BRAKE-L1" gate="G$1" pin="D"/>
<wire x1="-147.32" y1="83.82" x2="-147.32" y2="93.98" width="0.1524" layer="91"/>
<junction x="-147.32" y="111.76"/>
<label x="-149.86" y="111.76" size="1.778" layer="95" rot="R270"/>
<wire x1="-147.32" y1="93.98" x2="-147.32" y2="111.76" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="38.1" y1="20.32" x2="66.04" y2="20.32" width="0.1524" layer="91"/>
<label x="40.64" y="20.32" size="1.778" layer="95"/>
<junction x="66.04" y="20.32"/>
<pinref part="U$1" gate="G$1" pin="16"/>
<pinref part="BL" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BRAKE_R_-" class="0">
<segment>
<pinref part="BRAKE-R1" gate="G$1" pin="D"/>
<wire x1="-25.4" y1="83.82" x2="-25.4" y2="93.98" width="0.1524" layer="91"/>
<junction x="-25.4" y="111.76"/>
<label x="-27.94" y="111.76" size="1.778" layer="95" rot="R270"/>
<wire x1="-25.4" y1="93.98" x2="-25.4" y2="111.76" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="38.1" y1="15.24" x2="66.04" y2="15.24" width="0.1524" layer="91"/>
<label x="40.64" y="15.24" size="1.778" layer="95"/>
<label x="40.64" y="15.24" size="1.778" layer="95"/>
<junction x="66.04" y="15.24"/>
<pinref part="U$1" gate="G$1" pin="20"/>
<pinref part="BR" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BLINKER_L_FRONT_-" class="0">
<segment>
<pinref part="BLINKER-L1" gate="G$1" pin="D"/>
<wire x1="50.8" y1="83.82" x2="50.8" y2="111.76" width="0.1524" layer="91"/>
<junction x="50.8" y="111.76"/>
<label x="48.26" y="111.76" size="1.778" layer="95" rot="R270"/>
</segment>
<segment>
<wire x1="38.1" y1="22.86" x2="66.04" y2="22.86" width="0.1524" layer="91"/>
<label x="40.64" y="22.86" size="1.778" layer="95"/>
<junction x="66.04" y="22.86"/>
<pinref part="U$1" gate="G$1" pin="14"/>
<pinref part="BLLF" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BLINKER_L_BACK_-" class="0">
<segment>
<pinref part="BLINKER-L2" gate="G$1" pin="D"/>
<wire x1="88.9" y1="83.82" x2="88.9" y2="111.76" width="0.1524" layer="91"/>
<junction x="88.9" y="111.76"/>
<label x="86.36" y="111.76" size="1.778" layer="95" rot="R270"/>
</segment>
<segment>
<wire x1="38.1" y1="25.4" x2="66.04" y2="25.4" width="0.1524" layer="91"/>
<label x="40.64" y="25.4" size="1.778" layer="95"/>
<junction x="66.04" y="25.4"/>
<pinref part="U$1" gate="G$1" pin="12"/>
<pinref part="BLLB" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BLINKER_R_FRONT_-" class="0">
<segment>
<pinref part="BLINKER-R1" gate="G$1" pin="D"/>
<wire x1="127" y1="83.82" x2="127" y2="111.76" width="0.1524" layer="91"/>
<junction x="127" y="111.76"/>
<label x="124.46" y="111.76" size="1.778" layer="95" rot="R270"/>
</segment>
<segment>
<wire x1="38.1" y1="27.94" x2="66.04" y2="27.94" width="0.1524" layer="91"/>
<label x="40.64" y="27.94" size="1.778" layer="95"/>
<junction x="66.04" y="27.94"/>
<pinref part="U$1" gate="G$1" pin="10"/>
<pinref part="BLRF" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BLINKER_R_BACK_-" class="0">
<segment>
<pinref part="BLINKER-R2" gate="G$1" pin="D"/>
<wire x1="165.1" y1="83.82" x2="165.1" y2="111.76" width="0.1524" layer="91"/>
<junction x="165.1" y="111.76"/>
<label x="162.56" y="111.76" size="1.778" layer="95" rot="R270"/>
</segment>
<segment>
<wire x1="38.1" y1="30.48" x2="66.04" y2="30.48" width="0.1524" layer="91"/>
<label x="40.64" y="30.48" size="1.778" layer="95"/>
<junction x="66.04" y="30.48"/>
<pinref part="U$1" gate="G$1" pin="8"/>
<pinref part="BLRB" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="12V" class="0">
<segment>
<wire x1="-86.36" y1="124.46" x2="-86.36" y2="154.94" width="0.1524" layer="91"/>
<wire x1="-25.4" y1="124.46" x2="-25.4" y2="154.94" width="0.1524" layer="91"/>
<wire x1="50.8" y1="124.46" x2="50.8" y2="154.94" width="0.1524" layer="91"/>
<wire x1="88.9" y1="124.46" x2="88.9" y2="154.94" width="0.1524" layer="91"/>
<wire x1="127" y1="124.46" x2="127" y2="154.94" width="0.1524" layer="91"/>
<wire x1="165.1" y1="124.46" x2="165.1" y2="154.94" width="0.1524" layer="91"/>
<junction x="-86.36" y="124.46"/>
<junction x="-25.4" y="124.46"/>
<junction x="50.8" y="124.46"/>
<junction x="88.9" y="124.46"/>
<junction x="127" y="124.46"/>
<junction x="165.1" y="124.46"/>
<wire x1="-86.36" y1="154.94" x2="-25.4" y2="154.94" width="0.1524" layer="91"/>
<junction x="-25.4" y="154.94"/>
<wire x1="-25.4" y1="154.94" x2="50.8" y2="154.94" width="0.1524" layer="91"/>
<junction x="50.8" y="154.94"/>
<wire x1="50.8" y1="154.94" x2="88.9" y2="154.94" width="0.1524" layer="91"/>
<junction x="88.9" y="154.94"/>
<wire x1="88.9" y1="154.94" x2="127" y2="154.94" width="0.1524" layer="91"/>
<junction x="127" y="154.94"/>
<wire x1="127" y1="154.94" x2="165.1" y2="154.94" width="0.1524" layer="91"/>
<wire x1="-147.32" y1="124.46" x2="-147.32" y2="154.94" width="0.1524" layer="91"/>
<junction x="-147.32" y="124.46"/>
<wire x1="-162.56" y1="154.94" x2="-147.32" y2="154.94" width="0.1524" layer="91"/>
<junction x="-147.32" y="154.94"/>
<wire x1="-147.32" y1="154.94" x2="-86.36" y2="154.94" width="0.1524" layer="91"/>
<junction x="-162.56" y="154.94"/>
<label x="-162.56" y="154.94" size="1.778" layer="95"/>
<junction x="-86.36" y="154.94"/>
</segment>
<segment>
<wire x1="-5.08" y1="15.24" x2="22.86" y2="15.24" width="0.1524" layer="91"/>
<label x="-5.08" y="15.24" size="1.778" layer="95"/>
<junction x="-5.08" y="15.24"/>
<pinref part="U$1" gate="G$1" pin="19"/>
</segment>
<segment>
<wire x1="-5.08" y1="20.32" x2="22.86" y2="20.32" width="0.1524" layer="91"/>
<label x="-5.08" y="20.32" size="1.778" layer="95"/>
<junction x="-5.08" y="20.32"/>
<pinref part="U$1" gate="G$1" pin="15"/>
</segment>
<segment>
<wire x1="-5.08" y1="17.78" x2="22.86" y2="17.78" width="0.1524" layer="91"/>
<label x="-5.08" y="17.78" size="1.778" layer="95"/>
<junction x="-5.08" y="17.78"/>
<pinref part="U$1" gate="G$1" pin="17"/>
</segment>
<segment>
<wire x1="-5.08" y1="22.86" x2="22.86" y2="22.86" width="0.1524" layer="91"/>
<label x="-5.08" y="22.86" size="1.778" layer="95"/>
<junction x="-5.08" y="22.86"/>
<pinref part="U$1" gate="G$1" pin="13"/>
</segment>
<segment>
<label x="-5.08" y="25.4" size="1.778" layer="95"/>
<wire x1="-5.08" y1="25.4" x2="22.86" y2="25.4" width="0.1524" layer="91"/>
<junction x="-5.08" y="25.4"/>
<pinref part="U$1" gate="G$1" pin="11"/>
</segment>
<segment>
<wire x1="-5.08" y1="27.94" x2="22.86" y2="27.94" width="0.1524" layer="91"/>
<label x="-5.08" y="27.94" size="1.778" layer="95"/>
<junction x="-5.08" y="27.94"/>
<pinref part="U$1" gate="G$1" pin="9"/>
</segment>
<segment>
<wire x1="-5.08" y1="30.48" x2="22.86" y2="30.48" width="0.1524" layer="91"/>
<label x="-5.08" y="30.48" size="1.778" layer="95"/>
<junction x="-5.08" y="30.48"/>
<pinref part="U$1" gate="G$1" pin="7"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="1"/>
<wire x1="91.44" y1="-10.16" x2="83.82" y2="-10.16" width="0.1524" layer="91"/>
<junction x="83.82" y="-10.16"/>
<label x="83.82" y="-10.16" size="1.778" layer="95"/>
<pinref part="12V" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BLINKER_L" class="0">
<segment>
<pinref part="BLINKER-L1" gate="G$1" pin="G"/>
<wire x1="45.72" y1="76.2" x2="20.32" y2="76.2" width="0.1524" layer="91"/>
<pinref part="R5" gate="G$1" pin="2"/>
<junction x="20.32" y="76.2"/>
<label x="20.32" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="BLINKER-L2" gate="G$1" pin="G"/>
<pinref part="R6" gate="G$1" pin="2"/>
<junction x="58.42" y="76.2"/>
<wire x1="58.42" y1="76.2" x2="83.82" y2="76.2" width="0.1524" layer="91"/>
<label x="58.42" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="81.28" y1="0" x2="66.04" y2="0" width="0.1524" layer="91"/>
<label x="66.04" y="0" size="1.778" layer="95"/>
<junction x="66.04" y="0"/>
<pinref part="R10" gate="G$1" pin="2"/>
<pinref part="BLC" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BLINKER_R" class="0">
<segment>
<pinref part="BLINKER-R1" gate="G$1" pin="G"/>
<wire x1="121.92" y1="76.2" x2="96.52" y2="76.2" width="0.1524" layer="91"/>
<pinref part="R14" gate="G$1" pin="2"/>
<junction x="96.52" y="76.2"/>
<label x="96.52" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="BLINKER-R2" gate="G$1" pin="G"/>
<wire x1="160.02" y1="76.2" x2="134.62" y2="76.2" width="0.1524" layer="91"/>
<pinref part="R15" gate="G$1" pin="2"/>
<junction x="134.62" y="76.2"/>
<label x="134.62" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="66.04" y1="2.54" x2="81.28" y2="2.54" width="0.1524" layer="91"/>
<label x="66.04" y="2.54" size="1.778" layer="95"/>
<junction x="66.04" y="2.54"/>
<pinref part="R7" gate="G$1" pin="1"/>
<pinref part="BRC" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="BRAKE" class="0">
<segment>
<pinref part="BRAKE-C1" gate="G$1" pin="G"/>
<wire x1="-91.44" y1="76.2" x2="-104.14" y2="76.2" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="2"/>
<junction x="-104.14" y="76.2"/>
<label x="-104.14" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="BRAKE-R1" gate="G$1" pin="G"/>
<wire x1="-30.48" y1="76.2" x2="-43.18" y2="76.2" width="0.1524" layer="91"/>
<pinref part="R3" gate="G$1" pin="2"/>
<junction x="-43.18" y="76.2"/>
<label x="-43.18" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="81.28" y1="-2.54" x2="66.04" y2="-2.54" width="0.1524" layer="91"/>
<label x="66.04" y="-2.54" size="1.778" layer="95"/>
<junction x="66.04" y="-2.54"/>
<pinref part="R9" gate="G$1" pin="2"/>
<pinref part="B" gate="G$1" pin="TP"/>
</segment>
<segment>
<pinref part="BRAKE-L1" gate="G$1" pin="G"/>
<wire x1="-152.4" y1="76.2" x2="-165.1" y2="76.2" width="0.1524" layer="91"/>
<pinref part="R16" gate="G$1" pin="2"/>
<junction x="-165.1" y="76.2"/>
<label x="-165.1" y="76.2" size="1.778" layer="95"/>
</segment>
</net>
<net name="BRAKE_C_-" class="0">
<segment>
<pinref part="BRAKE-C1" gate="G$1" pin="D"/>
<wire x1="-86.36" y1="83.82" x2="-86.36" y2="93.98" width="0.1524" layer="91"/>
<junction x="-86.36" y="111.76"/>
<label x="-88.9" y="111.76" size="1.778" layer="95" rot="R270"/>
<wire x1="-86.36" y1="93.98" x2="-86.36" y2="111.76" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="38.1" y1="17.78" x2="66.04" y2="17.78" width="0.1524" layer="91"/>
<label x="40.64" y="17.78" size="1.778" layer="95"/>
<junction x="66.04" y="17.78"/>
<pinref part="U$1" gate="G$1" pin="18"/>
<pinref part="BC" gate="G$1" pin="TP"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="X1" gate="-1" pin="S"/>
<pinref part="R7" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="X1" gate="-2" pin="S"/>
<pinref part="R10" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="X1" gate="-3" pin="S"/>
<pinref part="R9" gate="G$1" pin="1"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="115,1,30.48,23.0547,SV1,,,,,"/>
<approved hash="117,1,-95.25,63.5,GND,,,,,"/>
</errors>
</schematic>
</drawing>
</eagle>