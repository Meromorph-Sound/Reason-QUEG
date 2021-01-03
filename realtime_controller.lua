format_version = "1.0"

function append(list1,list2)
  for k, v in pairs(list2) do
    table.insert(list1,v)
  end
  return list1
end  

function propName(prop)
  return "/custom_properties/"..prop
end
function cvInputName(cv)
  return "/cv_inputs/"..cv
end



local channelNotes = {
  "x",
  "y",
  "level",
  "source",
  "VCOstart"
}
local simpleNotes = {
  "VCOactive",
  "VCOfreeze",
  "VCOzero",
  "VCOfrequency",
  "VCOwidth",
  "VCOheight",
  "VCOpattern",
  "builtin_onoffbypass"
}
local cvChangeNotes = {
}

local notes = {}

for k,v in pairs(channelNotes) do
    for n = 1,4 do
      table.insert(notes,propName(v)..n)
    end
  end
  
for k,v in pairs(simpleNotes) do
    table.insert(notes,propName(v))
  end
  
 for k,v in pairs(cvChangeNotes) do
    table.insert(notes,cvInputName(v))
    table.insert(notes,cvInputName(v).."/connected")
  end  



jbox.trace("Made notifications:")
jbox.trace(table.concat(notes,', '))
rt_input_setup = {
  notify = notes
}

rtc_bindings = { 
	{ source = "/environment/system_sample_rate", dest = "/global_rtc/init_instance" },
	{ source = "/environment/instance_id", dest = "/global_rtc/init_instance" },
}

global_rtc = { 

	init_instance = function(source_property_path, instance_id)
		local new_no = jbox.make_native_object_rw("Instance", {instance_id})
		jbox.store_property("/custom_properties/instance", new_no);
	end,
}

sample_rate_setup = { 
native = {
		22050,
		44100,
		48000,
		88200,
		96000,
		192000
	},
}




