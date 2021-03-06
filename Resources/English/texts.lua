format_version = "1.0"
 

function insert(table,tags) 
  for tag, text in pairs(tags) do
    for n=1, 4 do
      table["propertyname_"..tag..n] = text.." "..n
    end
  end
end

function properties(table,tags) 
  for k, tag in pairs(tags) do
    table[tag]=string.upper(tag)
    for n=1, 4 do
      table["propertyname_"..tag..n] = tag.." "..n
      table[tag..n]=string.upper(tag).." "..n
    end
  end
end

function cvs(table,tags)
  for idx,tag in pairs(tags) do
    for n=1, 4 do
      table[tag..n.."In"] = tag.." "..n.." input"
      table[tag..n.."Out"] = tag.." "..n.." output"
    end
  end
end

function vco(table,tags)
  for k, tag in pairs(tags) do
    table["propertyname_VCO"..tag] = "VCO "..tag
  end
end

function vco_insert(table,tags) 
  for tag, text in pairs(tags) do
      table["propertyname_"..tag] = text
  end
end
  

texts = {
  ["on"] = "On",
  ["off"] = "Off",
  ["n/a"] = "N/A",
  ["VCO"] = "VCO",
  ["manual"] = "Manual",
  ["bypass"] = "Bypass",
  ["audioInput1"] = "In 1",
  ["audioInput2"] = "In 2",
  ["audioInput3"] = "In 3",
  ["audioInput4"] = "In 4",
  ["audioOutputA"] = "Out A",
  ["audioOutputB"] = "Out B",
  ["audioOutputC"] = "Out C",
  ["audioOutputD"] = "Out D",
  ["setController"] = "Set controller position",
  ["resetController"] = "Revert controller position",
  ["vcoXIn"] = "VCO X input",
  ["vcoYIn"] = "VCO Y input",
  ["propertyname_VCOXTrim"] = "VCO X trim",
  ["propertyname_VCOYTrim"] = "VCO Y trim",
  ["vcoXOut"] = "VCO X output",
  ["vcoYOut"] = "VCO Y output",
  ["vcoMin"] = "75ms",
  ["vcoMax"] = "75s",
  ["vcoFms"] = "^0ms",
  ["vcoFs"] = "^0s",
  ["vcoSquareCW"] = "Square Clockwise",
  ["vcoSquareCCW"] = "Square Counterclockwise",
  ["vcoLR"] = "Left - Right",
  ["vcoUD"] = "Up - Down",
  ["vcoX"] = "Diagonal cross",
  ["vcoTLBR"] = "Diagonal TL - BR",
  ["vcoTRBL"] = "Diagonal TR - BL",
  ["vcoD"] = "Diamond",
  ["vco0"] = "75ms",
  ["vco1"] = "750ms",
  ["vco2"] = "7.5s"
 }
 
 properties(texts,{ "x", "y", "A", "B", "C", "D", "source", "level","xTrim","yTrim" } )
 cvs(texts,{ "X", "Y", "A", "B", "C", "D", "level", "mode"})
 vco(texts,{ "active", "freeze", "zero", "frequency", "width", "height", "pattern", 
             "start1", "start2", "start3", "start4" })
 insert(texts,{ ["source_shortest"] = "SR", 
                ["x_shortest"] = "X", 
                ["y_shortest"] = "Y", 
                ["level_shortest"] = "L" })
 vco_insert(texts, {
                ["VCOactive_shortest"] = "VA",
                ["VCOfreeze_shortest"] = "VH",
                ["VCOzero_shortest"] = "VZ",
                ["VCOfrequency_shortest"] = "VF",
                ["VCOwidth_shortest"] = "VW",
                ["VCOheight_shortest"] = "VH",
                ["VCOpattern_shortest"] = "VS" 
} )
 
 
