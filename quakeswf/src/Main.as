package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.utils.ByteArray;
	import cmodule.quake.CLibInit;
	import flash.utils.getTimer;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	import flash.net.SharedObject;
	
	
	/**
	 * ...
	 * @author Michael Rennie
	 */
	public class Main extends Sprite 
	{
		
		private var _swc:Object;
		private var _swcRam:ByteArray;
		
		private var _bitmapData:BitmapData;//This is null until after we have called the first _swc.swcFrame()
		private var _bitmap:Bitmap;
		private var _rect:Rectangle;
		
		[Embed(source="../embed/PAK0.PAK", mimeType="application/octet-stream")]
		private var Embed_pak:Class;
		
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
			
			var pakFile:ByteArray = new Embed_pak;
			var begintime:Number = getTimer() / 1000;
			_swcRam = _swc.swcInit(this, pakFile);
			
			stage.addEventListener(Event.ENTER_FRAME, onFrame);
			stage.addEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
			stage.addEventListener(KeyboardEvent.KEY_UP, onKeyUp);
		}
		
		private function onFrame(e:Event):void
		{
			var newTime:Number = getTimer() / 1000;
			var screenBufferPos:uint = _swc.swcFrame(newTime);
										
			if (!_bitmapData)
			{
				//Wait for the first frame before adding the bitmap.
				var width:uint = 640;
				var height:uint = 480;
				_bitmapData = new BitmapData(width, height, false);
				_rect = new Rectangle(0, 0, width, height);
				_bitmap = new Bitmap(_bitmapData);
				addChild(_bitmap);
			}
			
			_swcRam.position = screenBufferPos;
			_bitmapData.setPixels(_rect, _swcRam);
		}
		
		private function onKeyDown( e:KeyboardEvent ):void
		{
			//trace("onKeyDown: ", e.keyCode);
			_swc.swcKey(e.keyCode, 1);
		}
		private function onKeyUp( e:KeyboardEvent ):void
		{
			_swc.swcKey(e.keyCode, 0);
		}
		
		//SharedObjects are used to save quake config files	
		public function setSharedObject(name:String, value:String):void
		{
			var sharedObject:SharedObject = SharedObject.getLocal(name);
			
			if (!sharedObject)
				return;
				
			sharedObject.data.str = value;
			sharedObject.flush();
		}
		public function getSharedObject(name:String):String
		{
			var sharedObject:SharedObject = SharedObject.getLocal(name);
			if (!sharedObject)
				return null;
			
			if (!sharedObject.data.str)
				return null;
			
			return sharedObject.data.str;
		}
	}
	
}