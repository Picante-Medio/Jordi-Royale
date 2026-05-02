@tool
extends Component
class_name XPComponent

@export var experience:int = 5

func get_component() -> Dictionary[String, Variant]:
	return {
		"experience" : FormatWriter.format(experience, "experience"),
	}
