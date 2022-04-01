#ifndef EVENT_H
#define EVENT_H

enum chawm_event
{
	/// Spawn a program
	CHAWM_EVENT_SPAWN,

	/// Quit chawm
	CHAWM_EVENT_QUIT,

	/// The number of available chawm events
	CHAWM_EVENT_COUNT
};

#endif /* EVENT_H */
