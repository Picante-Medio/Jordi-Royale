@tool
extends Component
class_name ProjectileComponent

@export var lifetime:int
@export var pathTypeX:int = PathType::mru
@export var pathInfoX:Vector4 = HUGO::Vector4(0.f
@export var pathTypeY:int = PathType::mru
@export var pathInfoY:Vector4 = HUGO::Vector4(0.f
@export var pathTypeZ:int = PathType::mru
@export var pathInfoZ:Vector4 = HUGO::Vector4(0.f
@export var pathZ:ProjectilePath = MRU(

func get_component() -> Dictionary[String, Variant]:
	return {
		"lifetime" : FormatWriter.format(lifetime, "lifetime"),
		"pathTypeX" : FormatWriter.format(pathTypeX, "pathTypeX"),
		"pathInfoX" : FormatWriter.format(pathInfoX, "pathInfoX"),
		"pathTypeY" : FormatWriter.format(pathTypeY, "pathTypeY"),
		"pathInfoY" : FormatWriter.format(pathInfoY, "pathInfoY"),
		"pathTypeZ" : FormatWriter.format(pathTypeZ, "pathTypeZ"),
		"pathInfoZ" : FormatWriter.format(pathInfoZ, "pathInfoZ"),
		"pathZ" : FormatWriter.format(pathZ, "pathZ"),
	}
