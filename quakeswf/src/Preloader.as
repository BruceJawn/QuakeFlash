package
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.ProgressEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.text.TextFormatAlign;
	import flash.utils.getDefinitionByName;
	
	public class Preloader extends MovieClip {
		private var preloader		:Shape;
		private var progressText	:TextField;
		private var infoText		:TextField;
		
		public function Preloader() {
			
			//Entire application visible in the specified area without distortion while maintaining the original aspect ratio of the application.
			stage.scaleMode = StageScaleMode.SHOW_ALL;

			addEventListener(Event.ENTER_FRAME, checkFrame);
			loaderInfo.addEventListener(ProgressEvent.PROGRESS, progress);
			// show loader
			
			preloader = new Shape();
			preloader.graphics.beginFill(0xFFFFFF);
			preloader.graphics.drawRect( -15, -15, 30, 30);
			preloader.graphics.endFill();
			addChild(preloader);
			
			progressText = new TextField();
			progressText.selectable = false;
			var progressTextFormat:TextFormat = new TextFormat("_sans", 16, 0xFFFFFF, true);
			progressTextFormat.align = TextFormatAlign.CENTER;
			progressText.defaultTextFormat = progressTextFormat;
			addChild(progressText);
			
			infoText = new TextField();
			infoText.selectable = false;
			infoText.width = 300;
			infoText.defaultTextFormat = progressTextFormat;
			infoText.text = "Quake created by ID Software\nPorted to Flash by Michael Rennie";
			infoText.y = 200;
			addChild(infoText);
			
			stage.addEventListener(Event.RESIZE, onResize);
			onResize();
		}
		
		private function onResize(e:Event = null):void {
			if (preloader) {
				preloader.x = stage.stageWidth / 2;
				preloader.y = stage.stageHeight / 2;
			}
			if (progressText) {
				progressText.x = (stage.stageWidth - progressText.width) / 2;
				progressText.y = stage.stageHeight / 2 + 22;
				infoText.x = (stage.stageWidth - infoText.width) / 2;
				infoText.y = stage.stageHeight / 2 - infoText.height;
			}
		}
		
		private function progress(e:ProgressEvent):void {
			// update loader
			if (progressText) {
				progressText.text = Math.round(e.bytesLoaded/e.bytesTotal*100).toString() + " %";
			}
		}
		
		private function checkFrame(e:Event):void {
			preloader.rotation += 5;
			if (currentFrame == totalFrames) {
				removeEventListener(Event.ENTER_FRAME, checkFrame);
				startup();
			}
		}
		
		private function startup():void {
			// hide loader
			stop();
			removeChild(preloader);
			removeChild(progressText);
			removeChild(infoText);
			preloader = null;
			progressText = null;
			infoText = null;
			loaderInfo.removeEventListener(ProgressEvent.PROGRESS, progress);
			var mainClass:Class = getDefinitionByName("Main") as Class;
			addChildAt(new mainClass() as DisplayObject, 0);
		}
	}
}