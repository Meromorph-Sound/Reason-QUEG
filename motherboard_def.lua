format_version = "3.0"



function propName(tag) 
  return jbox.ui_text("propertyname_"..tag)
end



function makeGUIProperties()
  local props = {
    VCOactive = jbox.number {
     property_tag = 51,
     default = 0,
     steps = 2,
     ui_name = propName("VCOactive"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    },
    VCOfreeze = jbox.number {
     property_tag = 52,
     default = 0,
     steps = 2,
     ui_name = propName("VCOfreeze"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    },
    VCOzero = jbox.number {
     property_tag = 53,
     default = 0,
     steps = 2,
     ui_name = propName("VCOzero"),
     ui_type = jbox.ui_selector { jbox.UI_TEXT_ON, jbox.UI_TEXT_OFF }
    },
    VCOfrequency = jbox.number {
     property_tag = 54,
     default = 0,
     ui_name = propName("VCOfrequency"),
     ui_type = jbox.ui_percent({decimals=2}),
    },
    VCOwidth = jbox.number {
     property_tag = 55,
     default = 0.5,
     ui_name = propName("VCOwidth"),
     ui_type = jbox.ui_percent({decimals=2}),
    },
    VCOheight = jbox.number {
     property_tag = 56,
     default = 0.5,
     ui_name = propName("VCOheight"),
     ui_type = jbox.ui_percent({decimals=2}),
    },
    VCOpattern = jbox.number {
     property_tag = 60,
     default = 0,
     steps = 8,
     ui_name = propName("VCOpattern"),
     ui_type = jbox.ui_selector { 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"), 
      propName("VCOheight"),
      propName("VCOheight"),
      propName("VCOheight")
      }
    },
  }
  
  for n=1,4 do
    props["VCOstart"..n] = jbox.number {
     property_tag = 60+n,
     default = n-1,
     steps = 4,
     ui_name = propName("VCOstart"..n),
     ui_type = jbox.ui_selector { 
      jbox.ui_text("A"), 
      jbox.ui_text("B"), 
      jbox.ui_text("C"), 
      jbox.ui_text("D")
      }
    } 

    local base=(n-1)*10
    props["x"..n] = jbox.number {
      property_tag = 1+base,
      default = 0.5,
      ui_name = propName("x"..n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),
    }
    props["y"..n] = jbox.number {
      property_tag = 2+base,
      default = 0.5,
      ui_name = propName("y"..n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),    
    }
    props["level"..n] = jbox.number {
     property_tag = 3+base,
     default = 0.5,
     ui_name = propName("level"..n),
     ui_type = jbox.ui_percent({decimals=2}),
    }
    props["source"..n] = jbox.number {
     property_tag = 4+base,
     default = 1,
     steps = 3,
     ui_name = propName("source"..n),
     ui_type = jbox.ui_selector { jbox.ui_text("VCO"), jbox.ui_text("manual"), jbox.ui_text("bypass") }
    }

  end
  
  jbox.trace("Made GUI properties:")
  for k,v in pairs(props) do
    jbox.trace(k.." : "..tostring(v))
  end
  return props
end

function makeRTProperties()
  local props = {}
  for n = 1,4 do
    local base=(n-1)*10
    props["A"..n] = jbox.number { 
      property_tag = 6+base,
      default = 0.5,
      ui_name = propName("A"..n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props["B"..n] = jbox.number { 
      property_tag = 7+base,
      default = 0.5,
      ui_name = propName("B"..n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props["C"..n] = jbox.number { 
      property_tag = 8+base,
      default = 0.5,
      ui_name = propName("C"..n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    } 
    props["D"..n] = jbox.number { 
      property_tag = 9+base,
      default = 0.5,
      ui_name = propName("D"..n),
      ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}})
    }
  end
  jbox.trace("Made RT properties:")
  for k,v in pairs(props) do
    jbox.trace(k.." : "..tostring(v))
  end
  return props
end
    

custom_properties = jbox.property_set{	
  
	document_owner = { 
		properties =  makeGUIProperties()
	},
	rt_owner = {
	 properties = makeRTProperties()
	},
	rtc_owner = {
		properties = {
			instance = jbox.native_object{},
		}
	},
}




    
local midi={}
local cc=39
local props = {"level","x","y"}
for channel = 1,4 do
  for k,tag in pairs(props) do
    midi[cc] = "/custom_properties/"..tag..channel
    cc=cc+1
  end
end
midi_implementation_chart = { midi_cc_chart = midi }


local remote = {}
local remotes = {"level","x","y"}
for k, tag in pairs(remotes) do
  for channel = 1, 4 do
    local name=tag..channel
    local pn=propName(name)
    remote["/custom_properties/"..name] = {
      internal_name=name,
      short_ui_name=propName(name),
      shortest_ui_name=propName(tag.."_shortest"..channel)
    }
  end
end
remote_implementation_chart = remote


function audioIn(tag) 
  return jbox.audio_input{ ui_name = jbox.ui_text(tag) }
end

function audioOut(tag) 
  return jbox.audio_output{ ui_name = jbox.ui_text(tag) }
end

audio_inputs = {
  in1 = audioIn("audioInput1"),
  in2 = audioIn("audioInput2"),
  in3 = audioIn("audioInput3"),
  in4 = audioIn("audioInput4")
}

audio_outputs = {
  outA = audioOut("audioOutputA"),
  outB = audioOut("audioOutputB"),
  outC = audioOut("audioOutputC"),
  outD = audioOut("audioOutputD")
}

cv_inputs = {}
cv_outputs = {}
local tags = { "X", "Y" }
  for index, tag in pairs(tags) do
    for channel=1,4 do
      local name=tag..channel.."Out"
      cv_outputs[name] = jbox.cv_output{ ui_name = jbox.ui_text(name) }
    end
 end

cv_outputs["vcoXOut"] = jbox.cv_output{ ui_name = jbox.ui_text("vcoXOut") }
cv_outputs["vcoYOut"] = jbox.cv_output{ ui_name = jbox.ui_text("vcoYOut") }




