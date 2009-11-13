package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.utils.ByteArray;
	import cmodule.quake.CLibInit;
	
	/**
	 * ...
	 * @author Michael Rennie
	 */
	public class Main extends Sprite 
	{
		
		private var _swc:Object;
		private var _swcRam:ByteArray;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
						
			//init swc
			var loader:CLibInit = new CLibInit;
			_swc = loader.init();
			_swcRam = _swc.swcInit();
		}
		
	}
	
}