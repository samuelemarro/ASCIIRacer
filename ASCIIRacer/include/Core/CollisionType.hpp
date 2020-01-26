#pragma once

/// <summary>	Indica il tipo di collisione. </summary>
///
/// <remarks>	Se la collisione avviene in un vertice
/// 			dello sprite (es. in alto a sinistra),
/// 			verrà registrata su due lati. </remarks>

class CollisionType {
public:

	/// <summary>	True se la collisione è avvenuta in
	/// 			almeno una delle celle in alto. </summary>
	bool top;
	/// <summary>	True se la collisione è avvenuta in
	/// 			almeno una delle celle in basso. </summary>
	bool bottom;
	/// <summary>	True se la collisione è avvenuta in
	/// 			almeno una delle celle a sinistra. </summary>
	bool left;
	/// <summary>	True se la collisione è avvenuta in
	/// 			almeno una delle celle a destra. </summary>
	bool right;
	/// <summary>	True se la collisione è avvenuta in
	/// 			almeno una cella. </summary>
	bool any;

	/// <summary>	Costruttore di default. </summary>

	CollisionType();

	/// <summary>	Costruttore completo. </summary>
	///
	/// <remarks>	Utente, 26/01/2020. </remarks>
	///
	/// <param name="top">   	True se la collisione è
	/// 						avvenuta in almeno una
	/// 						delle celle in alto. </param>
	/// <param name="bottom">	True se la collisione è
	/// 						avvenuta in almeno una
	/// 						delle celle in basso. </param>
	/// <param name="left">  	True se la collisione è
	/// 						avvenuta in almeno una
	/// 						delle celle a sinistra. </param>
	/// <param name="right"> 	True se la collisione è
	/// 						avvenuta in almeno una
	/// 						delle celle a destra. </param>
	/// <param name="any">   	True se la collisione è
	/// 						avvenuta in almeno una
	/// 						cella. </param>

	CollisionType(bool top, bool bottom, bool left, bool right, bool any);
};